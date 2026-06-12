#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include "DesignByContract.h"

class Building {
private:
    std::string fName;
    std::string fIdentifier;
    std::string fCampusId;
    bool fProperlyInitialized;

public:
    /**
     * REQUIRE(!name.empty())
     * REQUIRE(!id.empty())
     * REQUIRE(!campusId.empty())
     * ENSURE(isProperlyInitialized())
     * ENSURE(getName() == name)
     * ENSURE(getIdentifier() == id)
     * ENSURE(getCampusId() == campusId)
     */
    Building(const std::string& name,
             const std::string& id,
             const std::string& campusId);

    /**
     * ENSURE(result == true || result == false)
     */
    bool isProperlyInitialized() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    const std::string& getName() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    const std::string& getIdentifier() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    const std::string& getCampusId() const;
};

#endif