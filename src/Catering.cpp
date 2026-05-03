#include "Catering.h"
#include "DesignByContract.h"

Catering::Catering(const std::string& provider, const std::string& buildingId) 
    : fProviderName(provider), fBuildingId(buildingId) {
    REQUIRE(!provider.empty(), "Catering provider mag niet leeg zijn");
    REQUIRE(!buildingId.empty(), "Gebouw ID voor catering mag niet leeg zijn");

    fProperlyInitialized = true;
    ENSURE(isProperlyInitialized(), "Catering niet correct geinitialiseerd");
}

bool Catering::isProperlyInitialized() const { return fProperlyInitialized; }
std::string Catering::getProviderName() const { return fProviderName; }
std::string Catering::getBuildingId() const { return fBuildingId; }