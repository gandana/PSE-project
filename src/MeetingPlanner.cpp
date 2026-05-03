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

    // 4. Meetings, 5. Renovations, 6. Catering...
    // (Gebruik de lussen die ik je in het vorige bericht gaf)

    doc.SaveFile(filename.c_str());
}