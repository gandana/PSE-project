#include "Campus.h"

Campus::Campus(const std::string& name, const std::string& id)
    : fName(name),
      fIdentifier(id),
      fProperlyInitialized(true) {

    REQUIRE(!name.empty(), "Campus name cannot be empty");
    REQUIRE(!id.empty(), "Campus identifier cannot be empty");

    ENSURE(isProperlyInitialized(),
           "Campus was not properly initialized");

    ENSURE(fName == name,
           "Campus name was not stored correctly");

    ENSURE(fIdentifier == id,
           "Campus identifier was not stored correctly");
}

bool Campus::isProperlyInitialized() const {
    return fProperlyInitialized;
}

const std::string& Campus::getName() const {
    REQUIRE(isProperlyInitialized(), "Campus not initialized");

    const std::string& result = fName;

    ENSURE(!result.empty(),
           "Campus name may not be empty");

    return result;
}

const std::string& Campus::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Campus not initialized");

    const std::string& result = fIdentifier;

    ENSURE(!result.empty(),
           "Campus identifier may not be empty");

    return result;
}