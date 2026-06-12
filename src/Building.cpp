#include "Building.h"

Building::Building(const std::string& name,
                   const std::string& id,
                   const std::string& campusId)
        : fName(name),
          fIdentifier(id),
          fCampusId(campusId),
          fProperlyInitialized(true) {

    REQUIRE(!name.empty(), "Building name cannot be empty");
    REQUIRE(!id.empty(), "Building identifier cannot be empty");
    REQUIRE(!campusId.empty(), "Building must belong to a campus");

    ENSURE(isProperlyInitialized(),
           "Building was not properly initialized");
    ENSURE(fName == name,
           "Building name was not stored correctly");
    ENSURE(fIdentifier == id,
           "Building identifier was not stored correctly");
    ENSURE(fCampusId == campusId,
           "Building campusId was not stored correctly");
}

bool Building::isProperlyInitialized() const {
    bool result = fProperlyInitialized;
    ENSURE(result == true || result == false,
           "Invalid initialization state");
    return result;
}

const std::string& Building::getName() const {
    REQUIRE(isProperlyInitialized(), "Building not initialized");

    const std::string& result = fName;

    ENSURE(!result.empty(),
           "Building name may not be empty");
    return result;
}

const std::string& Building::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Building not initialized");

    const std::string& result = fIdentifier;

    ENSURE(!result.empty(),
           "Building identifier may not be empty");
    return result;
}

const std::string& Building::getCampusId() const {
    REQUIRE(isProperlyInitialized(), "Building not initialized");

    const std::string& result = fCampusId;

    ENSURE(!result.empty(),
           "Building campusId may not be empty");
    return result;
}