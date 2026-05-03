#include "MeetingPlanner.h"
#include "tinyxml.h"
#include <algorithm>  // Nodig voor std::find
#include <iostream>   // Nodig voor std::cerr en std::cout


MeetingPlanner::MeetingPlanner() : fProperlyInitialized(true) {
    ENSURE(isProperlyInitialized(), "MeetingPlanner not properly initialized");
}

// De destructor: Verwijder alle 'new' objecten uit de parser!
MeetingPlanner::~MeetingPlanner() {
    for (Campus* c : fCampuses) delete c;
    for (Building* b : fBuildings) delete b;
    for (Room* r : fRooms) delete r;
    for (Meeting* m : fMeetings) delete m;
    for (Renovation* ren : fRenovations) delete ren;
    for (Catering* cat : fCaterings) delete cat;
}

void MeetingPlanner::addCampus(Campus* c) {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd");
    REQUIRE(c != nullptr, "Campus mag niet null zijn");
    fCampuses.push_back(c);
}

void MeetingPlanner::addBuilding(Building* b) {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd");
    REQUIRE(b != nullptr, "Building mag niet null zijn");
    fBuildings.push_back(b);
}

void MeetingPlanner::addRoom(Room* r) {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd");
    REQUIRE(r != nullptr, "Room mag niet null zijn");
    fRooms.push_back(r);
}

void MeetingPlanner::addRenovation(Renovation* ren) {
    REQUIRE(ren != nullptr, "Renovatie mag niet null zijn");
    fRenovations.push_back(ren);
}

void MeetingPlanner::addCatering(Catering* cat) {
    REQUIRE(cat != nullptr, "Catering mag niet null zijn");
    fCaterings.push_back(cat);
}

bool MeetingPlanner::isProperlyInitialized() const {
    return fProperlyInitialized;
}

void MeetingPlanner::exportSystem(const std::string& filename) const {
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
    doc.LinkEndChild(decl);

    TiXmlElement* root = new TiXmlElement("SYSTEM");
    doc.LinkEndChild(root);

    // 1. Campussen
    for (Campus* c : fCampuses) {
        TiXmlElement* cElem = new TiXmlElement("CAMPUS");
        TiXmlElement* name = new TiXmlElement("NAME");
        name->LinkEndChild(new TiXmlText(c->getName().c_str()));
        TiXmlElement* id = new TiXmlElement("IDENTIFIER");
        id->LinkEndChild(new TiXmlText(c->getIdentifier().c_str()));
        cElem->LinkEndChild(name);
        cElem->LinkEndChild(id);
        root->LinkEndChild(cElem);
    }

    // 2. Gebouwen
    for (Building* b : fBuildings) {
        TiXmlElement* bElem = new TiXmlElement("BUILDING");
        TiXmlElement* name = new TiXmlElement("NAME");
        name->LinkEndChild(new TiXmlText(b->getName().c_str()));
        TiXmlElement* id = new TiXmlElement("IDENTIFIER");
        id->LinkEndChild(new TiXmlText(b->getIdentifier().c_str()));
        TiXmlElement* camp = new TiXmlElement("CAMPUS");
        camp->LinkEndChild(new TiXmlText(b->getCampusId().c_str()));
        bElem->LinkEndChild(name);
        bElem->LinkEndChild(id);
        bElem->LinkEndChild(camp);
        root->LinkEndChild(bElem);
    }

    // 3. Kamers (Systeem 2.0)
    for (Room* r : fRooms) {
        TiXmlElement* rElem = new TiXmlElement("ROOM");
        TiXmlElement* name = new TiXmlElement("NAME");
        name->LinkEndChild(new TiXmlText(r->getName().c_str()));
        TiXmlElement* id = new TiXmlElement("IDENTIFIER");
        id->LinkEndChild(new TiXmlText(r->getIdentifier().c_str()));
        TiXmlElement* cap = new TiXmlElement("CAPACITY");
        cap->LinkEndChild(new TiXmlText(std::to_string(r->getCapacity()).c_str()));
        TiXmlElement* camp = new TiXmlElement("CAMPUS");
        camp->LinkEndChild(new TiXmlText(r->getCampusId().c_str()));
        TiXmlElement* build = new TiXmlElement("BUILDING");
        build->LinkEndChild(new TiXmlText(r->getBuildingId().c_str()));

        rElem->LinkEndChild(name);
        rElem->LinkEndChild(id);
        rElem->LinkEndChild(cap);
        rElem->LinkEndChild(camp);
        rElem->LinkEndChild(build);
        root->LinkEndChild(rElem);
    }

    // 4. Meetings
    for (Meeting* m : fMeetings) {
        TiXmlElement* mElem = new TiXmlElement("MEETING");
        TiXmlElement* label = new TiXmlElement("LABEL");
        label->LinkEndChild(new TiXmlText(m->getLabel().c_str()));
        TiXmlElement* id = new TiXmlElement("IDENTIFIER");
        id->LinkEndChild(new TiXmlText(m->getIdentifier().c_str()));
        TiXmlElement* room = new TiXmlElement("ROOM");
        room->LinkEndChild(new TiXmlText(m->getRoomId().c_str()));

        // Zorg dat je een getDateString() of iets dergelijks in je Meeting klasse hebt
        TiXmlElement* date = new TiXmlElement("DATE");
        date->LinkEndChild(new TiXmlText(m->getDateString().c_str()));

        mElem->LinkEndChild(label);
        mElem->LinkEndChild(id);
        mElem->LinkEndChild(room);
        mElem->LinkEndChild(date);
        root->LinkEndChild(mElem);
    }

    // 5. Renovations
    for (Renovation* ren : fRenovations) {
        TiXmlElement* renElem = new TiXmlElement("RENOVATION");
        TiXmlElement* room = new TiXmlElement("ROOM");
        room->LinkEndChild(new TiXmlText(ren->getRoomId().c_str()));
        TiXmlElement* start = new TiXmlElement("START");
        start->LinkEndChild(new TiXmlText(std::to_string(ren->getStartDay()).c_str()));
        TiXmlElement* end = new TiXmlElement("END");
        end->LinkEndChild(new TiXmlText(std::to_string(ren->getEndDay()).c_str()));

        renElem->LinkEndChild(room);
        renElem->LinkEndChild(start);
        renElem->LinkEndChild(end);
        root->LinkEndChild(renElem);
    }

    // 6. Catering
    for (Catering* cat : fCaterings) {
        TiXmlElement* catElem = new TiXmlElement("CATERING");
        TiXmlElement* prov = new TiXmlElement("PROVIDER");
        prov->LinkEndChild(new TiXmlText(cat->getProviderName().c_str()));
        TiXmlElement* build = new TiXmlElement("BUILDING");
        build->LinkEndChild(new TiXmlText(cat->getBuildingId().c_str()));

        catElem->LinkEndChild(prov);
        catElem->LinkEndChild(build);
        root->LinkEndChild(catElem);
    }

    doc.SaveFile(filename.c_str());
}

void MeetingPlanner::addParticipation(const std::string& meetingId, const std::string& userId, bool isExternal) {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd");

    for (Meeting* m : fMeetings) {
        if (m->getIdentifier() == meetingId) {
            // Nu geven we ook door of de persoon extern is
            m->addParticipant(userId, isExternal);
            return;
        }
    }
    std::cerr << "Fout: Kan deelnemer " << userId << " niet toevoegen aan onbekende meeting " << meetingId << std::endl;
}

void MeetingPlanner::runSimulation() {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd voor simulatie");

    std::cout << "\n--- START SIMULATIE ---\n" << std::endl;

    // Eerst alle logica uitvoeren (capaciteit, renovatie, overlappingen)
    processAllMeetings();

    double totaalCO2 = 0.0;
    int totaalDeelnemers = 0;
    int aantalMeetings = 0;

    for (Meeting* m : fMeetings) {
        if (m->isCanceled()) {
            std::cout << "[GEANNULEERD] " << m->getLabel() << " (ID: " << m->getIdentifier() << ")" << std::endl;
        } else {
            // Bereken CO2 voor deze specifieke meeting
            double meetingCO2 = m->calculateCO2();
            totaalCO2 += meetingCO2;

            // VOEG DEZE TWEE REGELS TOE:
            totaalDeelnemers += m->getParticipantCount(); // Voor punt 3.10
            aantalMeetings++;                             // Voor punt 3.10

            std::cout << "[OK] " << m->getLabel()
                      << " | Deelnemers: " << m->getParticipantCount()
                      << " | CO2: " << meetingCO2 << "g" << std::endl;
        }
    }
    // Statistieken (Punt 3.10)
    std::cout << "Gemiddeld aantal deelnemers per meeting: "
              << (aantalMeetings > 0 ? (double)totaalDeelnemers / aantalMeetings : 0) << std::endl;

    // Catering check (Punt 1.4)
    std::cout << "\nCatering Overzicht:" << std::endl;
    for (Catering* cat : fCaterings) {
        std::cout << "- Provider " << cat->getProviderName()
                  << " bedient gebouw " << cat->getBuildingId() << std::endl;
    }
}


void MeetingPlanner::processAllMeetings() {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd");

    for (Meeting* m : fMeetings) {
        // --- STAP 0: CHECK ONLINE STATUS (Use Case 3.4) ---
        if (m->isOnline()) {
            m->setProcessed(true);
            m->setCanceled(false); // Online gaat altijd door
            continue; // Sla alle kamer-checks over!
        }

        // 1. Zoek de kamer (alleen voor fysieke meetings)
        Room* targetRoom = nullptr;
        for (Room* r : fRooms) {
            if (r->getIdentifier() == m->getRoomId()) {
                targetRoom = r;
                break;
            }
        }

        if (targetRoom == nullptr) {
            m->setCanceled(true);
            m->setProcessed(true);
            continue;
        }

        // --- CHECK 1: CAPACITEIT ---
        if (m->getParticipants().size() > (size_t)targetRoom->getCapacity()) {
            std::cout << "[CAPACITEIT FOUT] Meeting " << m->getLabel()
                      << " past niet in " << targetRoom->getName() << std::endl; // Punt 3.6
            m->setCanceled(true);
        }

        // Datum berekenen
        std::time_t meetingTime = std::chrono::system_clock::to_time_t(m->getDate());
        int meetingDay = std::localtime(&meetingTime)->tm_yday + 1;

        // --- CHECK 2: RENOVATIES (Use Case 3.3) ---
        if (!m->isCanceled()) {
            for (Renovation* ren : fRenovations) {
                if (ren->getRoomId() == m->getRoomId()) {
                    if (meetingDay >= ren->getStartDay() && meetingDay <= ren->getEndDay()) {
                        m->setCanceled(true);
                        break;
                    }
                }
            }
        }

        // --- CHECK 3: OVERLAPPINGEN ---
        if (!m->isCanceled()) {
            for (Meeting* other : fMeetings) {
                if (other == m) continue;
                if (!other->isProcessed() || other->isCanceled() || other->isOnline()) continue;

                if (other->getRoomId() == m->getRoomId()) {
                    std::time_t otherTime = std::chrono::system_clock::to_time_t(other->getDate());
                    int otherDay = std::localtime(&otherTime)->tm_yday + 1;

                    if (meetingDay == otherDay) {
                        m->setCanceled(true);
                        break;
                    }
                }
            }
        }

        m->setProcessed(true);
    }
}

void MeetingPlanner::addMeeting(Meeting* m) {
    REQUIRE(this->isProperlyInitialized(), "MeetingPlanner was niet correct geïnitialiseerd");
    REQUIRE(m != nullptr, "Kan geen null-pointer als meeting toevoegen");

    fMeetings.push_back(m);

    ENSURE(std::find(fMeetings.begin(), fMeetings.end(), m) != fMeetings.end(),
           "Meeting is niet correct toegevoegd aan de lijst");
}

bool MeetingPlanner::campusExists(const std::string& id) const {
    for (Campus* c : fCampuses) {
        if (c->getIdentifier() == id) return true;
    }
    return false;
}

bool MeetingPlanner::buildingExists(const std::string& id) const {
    for (Building* b : fBuildings) {
        if (b->getIdentifier() == id) return true;
    }
    return false;
}