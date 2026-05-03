#include "MeetingPlanner.h"
#include "tinyxml.h"


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
        // date->LinkEndChild(new TiXmlText(m->getDateString().c_str()));

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

void MeetingPlanner::addParticipation(const std::string& meetingId, const std::string& userId) {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd");

    // We lopen door al onze meetings heen om de juiste te vinden
    for (Meeting* m : fMeetings) {
        // Is dit de meeting die in de XML wordt genoemd?
        if (m->getIdentifier() == meetingId) {
            // Ja! Voeg de user toe aan de lijst van deze specifieke meeting
            m->addParticipant(userId);
            return; // We zijn klaar, we kunnen stoppen met zoeken
        }
    }

    // Als we hier komen, bestond de meetingId niet in onze lijst
    std::cerr << "Fout: Kan deelnemer " << userId << " niet toevoegen aan onbekende meeting " << meetingId << std::endl;
}

void MeetingPlanner::runSimulation() {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd voor simulatie");

    std::cout << "\n--- START SIMULATIE ---\n" << std::endl;

    for (Meeting* m : fMeetings) {
        // 1. Zoek de kamer die bij deze meeting hoort
        Room* targetRoom = nullptr;
        for (Room* r : fRooms) {
            if (r->getIdentifier() == m->getRoomId()) {
                targetRoom = r;
                break;
            }
        }

        // Check of de kamer bestaat
        if (targetRoom == nullptr) {
            m->setCanceled(true);
            continue;
        }

        // 2. De eigenlijke check (Punt 3.1 & 3.2 van je lijst)
        int aantalDeelnemers = m->getParticipants().size();
        int capaciteitKamer = targetRoom->getCapacity();

        if (aantalDeelnemers > capaciteitKamer) {
            m->setCanceled(true); // Te veel mensen -> annuleren
            std::cout << "[GEANNULEERD] " << m->getLabel() << " past niet in " << targetRoom->getName() << std::endl;
        } else {
            m->setCanceled(false); // Past wel -> OK!
            std::cout << "[OK] " << m->getLabel() << " kan doorgaan." << std::endl;
        }
        m->setProcessed(true); // Markeer als gecheckt
    }
    std::cout << "\n--- EINDE SIMULATIE ---\n" << std::endl;
}

void MeetingPlanner::processAllMeetings() {
    REQUIRE(isProperlyInitialized(), "Planner niet geïnitialiseerd");

    std::cout << "Bezig met verwerken van alle meetings...\n";

    for (Meeting* m : fMeetings) {
        // 1. Zoek de kamer op
        Room* targetRoom = nullptr;
        for (Room* r : fRooms) {
            if (r->getIdentifier() == m->getRoomId()) {
                targetRoom = r;
                break;
            }
        }

        if (targetRoom == nullptr) {
            m->setCanceled(true);
            continue;
        }

        // 2. Check capaciteit
        int aantalDeelnemers = m->getParticipants().size();
        if (aantalDeelnemers > targetRoom->getCapacity()) {
            m->setCanceled(true);
        } else {
            m->setCanceled(false);
        }
        m->setProcessed(true);
    }
}