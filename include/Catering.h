#ifndef CATERING_H
#define CATERING_H

#include <string>

class Catering {
private:
    std::string fProviderName;
    std::string fBuildingId;
    bool fProperlyInitialized;

public:

    /**
     * REQUIRE(!provider.empty())
     * REQUIRE(!buildingId.empty())
     * ENSURE(isProperlyInitialized())
     * ENSURE(getProviderName() == provider)
     * ENSURE(getBuildingId() == buildingId)
     */
    Catering(const std::string& provider,
             const std::string& buildingId);

    /**
     * ENSURE(result == true || result == false)
     */
    bool isProperlyInitialized() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    std::string getProviderName() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    std::string getBuildingId() const;
};

#endif