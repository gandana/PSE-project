#include "Room.h"

Room::Room(const std::string& name,
           const std::string& id,
           int capacity,
           const std::string& campusId,
           const std::string& buildingId)
        : fName(name),
          fIdentifier(id),
          fCapacity(capacity),
          fCampusId(campusId),
          fBuildingId(buildingId),
          fProperlyInitialized(false) {

    REQUIRE(!name.empty(), "Name cannot be empty");
    REQUIRE(!id.empty(), "Identifier cannot be empty");
    REQUIRE(capacity > 0, "Capacity must be strictly greater than 0");
    REQUIRE(!campusId.empty(), "Campus ID cannot be empty");
    REQUIRE(!buildingId.empty(), "Building ID cannot be empty");

    fProperlyInitialized = true;

    ENSURE(isProperlyInitialized(), "Room not properly initialized");
    ENSURE(fName == name, "Name was not set correctly");
    ENSURE(fIdentifier == id, "Identifier was not set correctly");
    ENSURE(fCapacity == capacity, "Capacity was not set correctly");
    ENSURE(fCampusId == campusId, "Campus ID was not set correctly");
    ENSURE(fBuildingId == buildingId, "Building ID was not set correctly");
}

bool Room::isProperlyInitialized() const {
    bool result = fProperlyInitialized;
    ENSURE(result == true || result == false, "Invalid initialization state");
    return result;
}

const std::string& Room::getName() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");

    const std::string& result = fName;
    ENSURE(!result.empty(), "Name may not be empty");
    return result;
}

const std::string& Room::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");

    const std::string& result = fIdentifier;
    ENSURE(!result.empty(), "Identifier may not be empty");
    return result;
}

int Room::getCapacity() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");

    int result = fCapacity;
    ENSURE(result > 0, "Capacity must be positive");
    return result;
}

const std::string& Room::getCampusId() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");

    const std::string& result = fCampusId;
    ENSURE(!result.empty(), "Campus ID may not be empty");
    return result;
}

const std::string& Room::getBuildingId() const {
    REQUIRE(isProperlyInitialized(), "Room not properly initialized");

    const std::string& result = fBuildingId;
    ENSURE(!result.empty(), "Building ID may not be empty");
    return result;
}