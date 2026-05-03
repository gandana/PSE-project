#include "Campus.h"

Campus::Campus(const std::string& name, const std::string& id)
    : fName(name), fIdentifier(id), fProperlyInitialized(true) {
    
    // Appendix A: NAME en IDENTIFIER mogen niet leeg zijn
    REQUIRE(!name.empty(), "Campus name cannot be empty");
    REQUIRE(!id.empty(), "Campus identifier cannot be empty");
    
    ENSURE(isProperlyInitialized(), "Campus was not properly initialized");
}

bool Campus::isProperlyInitialized() const {
    return fProperlyInitialized;
}

const std::string& Campus::getName() const {
    REQUIRE(isProperlyInitialized(), "Campus not initialized");
    return fName;
}

const std::string& Campus::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Campus not initialized");
    return fIdentifier;
}