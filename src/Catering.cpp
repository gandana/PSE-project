#include "Catering.h"
#include "DesignByContract.h"

Catering::Catering(const std::string& provider,
                   const std::string& buildingId)
        : fProviderName(provider),
          fBuildingId(buildingId),
          fProperlyInitialized(false) {

    REQUIRE(!provider.empty(),
            "Catering provider mag niet leeg zijn");

    REQUIRE(!buildingId.empty(),
            "Gebouw ID voor catering mag niet leeg zijn");

    fProperlyInitialized = true;

    ENSURE(isProperlyInitialized(),
           "Catering niet correct geinitialiseerd");

    ENSURE(fProviderName == provider,
           "Provider niet correct opgeslagen");

    ENSURE(fBuildingId == buildingId,
           "Building ID niet correct opgeslagen");
}

bool Catering::isProperlyInitialized() const {
    bool result = fProperlyInitialized;

    ENSURE(result == true || result == false,
           "Invalid initialization state");

    return result;
}

std::string Catering::getProviderName() const {
    REQUIRE(isProperlyInitialized(),
            "Catering niet correct geinitialiseerd");

    std::string result = fProviderName;

    ENSURE(!result.empty(),
           "Provider naam mag niet leeg zijn");

    return result;
}

std::string Catering::getBuildingId() const {
    REQUIRE(isProperlyInitialized(),
            "Catering niet correct geinitialiseerd");

    std::string result = fBuildingId;

    ENSURE(!result.empty(),
           "Building ID mag niet leeg zijn");

    return result;
}