#include "Room.h"

Room::Room(const std::string& name, const std::string& id, int capacity)
    : fName(name), fIdentifier(id), fCapacity(capacity), fProperlyInitialized(true) {
    
    // Design by Contract: Precondities uit Appendix A
    REQUIRE(!name.empty(), "Room name cannot be empty");
    REQUIRE(!id.empty(), "Room identifier cannot be empty");
    REQUIRE(capacity > 0, "Capacity should be an integer strictly greater than 0");
    
    ENSURE(isProperlyInitialized(), "Room was not properly initialized");
}

bool Room::isProperlyInitialized() const {
    return fProperlyInitialized;
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