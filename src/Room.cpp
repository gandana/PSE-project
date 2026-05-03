#include "Room.h"

// De constructor moet exact deze 5 parameters hebben zoals in je .h
// De constructor moet exact deze 5 parameters hebben zoals in je .h
Room::Room(const std::string& name, const std::string& id, int capacity,
           const std::string& campusId, const std::string& buildingId)
    : fName(name), fIdentifier(id), fCapacity(capacity),
      fCampusId(campusId), fBuildingId(buildingId), fProperlyInitialized(false) {

    REQUIRE(!name.empty(), "Name cannot be empty");
    REQUIRE(!id.empty(), "Identifier cannot be empty");
    REQUIRE(!campusId.empty(), "Campus ID cannot be empty");
    REQUIRE(!buildingId.empty(), "Building ID cannot be empty");

    // DIT IS DE REGEL DIE HET VERSCHIL MAAKT:
    REQUIRE(capacity > 0, "Capacity must be strictly greater than 0");


    fProperlyInitialized = true;
    ENSURE(isProperlyInitialized(), "Room not properly initialized");
}

bool Room::isProperlyInitialized() const {
    return fProperlyInitialized;
}

const std::string& Room::getName() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");
    return fName;
}

const std::string& Room::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");
    return fIdentifier;
}

int Room::getCapacity() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");
    return fCapacity;
}

const std::string& Room::getCampusId() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");
    return fCampusId;
}

const std::string& Room::getBuildingId() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");
    return fBuildingId;
}