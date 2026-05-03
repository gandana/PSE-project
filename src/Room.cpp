#include "Room.h"

Room::Room(const std::string& name, const std::string& id, int capacity,
           const std::string& campusId, const std::string& buildingId)
    : fName(name), fIdentifier(id), fCapacity(capacity),
      fCampusId(campusId), fBuildingId(buildingId), fProperlyInitialized(true) {

    REQUIRE(!name.empty(), "Room name cannot be empty");
    REQUIRE(!id.empty(), "Room identifier cannot be empty");
    REQUIRE(capacity > 0, "Capacity must be > 0");
    REQUIRE(!campusId.empty(), "Room must have a campus ID");   //[cite: 1]
    REQUIRE(!buildingId.empty(), "Room must have a building ID"); //[cite: 1]

    ENSURE(isProperlyInitialized(), "Room was not properly initialized");
}

const std::string& Room::getName() const {
    REQUIRE(isProperlyInitialized(), "Room not initialized");
    return fName;
}

const std::string& Room::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Room not initialized");
    return fIdentifier;
}

int Room::getCapacity() const {
    REQUIRE(isProperlyInitialized(), "Room not initialized");
    return fCapacity;
}

bool Room::isProperlyInitialized() const {
    return fProperlyInitialized;
}
const std::string& Room::getCampusId() const {
    REQUIRE(isProperlyInitialized(), "Room not initialized");
    return fCampusId;
}

const std::string& Room::getBuildingId() const {
    REQUIRE(isProperlyInitialized(), "Room not initialized");
    return fBuildingId;
}