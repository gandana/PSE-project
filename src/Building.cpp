#include "Building.h"

Building::Building(const std::string& name, const std::string& id, const std::string& campusId)
    : fName(name), fIdentifier(id), fCampusId(campusId), fProperlyInitialized(true) {
    
    REQUIRE(!name.empty(), "Building name cannot be empty");
    REQUIRE(!id.empty(), "Building identifier cannot be empty");
    REQUIRE(!campusId.empty(), "Building must belong to a campus (campusId cannot be empty)");
    
    ENSURE(isProperlyInitialized(), "Building was not properly initialized");
}

bool Building::isProperlyInitialized() const {
    return fProperlyInitialized;
}

const std::string& Building::getName() const {
    REQUIRE(isProperlyInitialized(), "Building not initialized");
    return fName;
}

const std::string& Building::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Building not initialized");
    return fIdentifier;
}

const std::string& Building::getCampusId() const {
    REQUIRE(isProperlyInitialized(), "Building not initialized");
    return fCampusId;
}