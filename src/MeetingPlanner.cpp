#include "MeetingPlanner.h"


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