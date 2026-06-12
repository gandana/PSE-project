#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "DesignByContract.h"

class Room {
private:
    std::string fName;
    std::string fIdentifier;
    int fCapacity;
    std::string fCampusId;
    std::string fBuildingId;
    bool fProperlyInitialized;

public:
    /**
     * REQUIRE(!name.empty())
     * REQUIRE(!id.empty())
     * REQUIRE(capacity > 0)
     * REQUIRE(!campusId.empty())
     * REQUIRE(!buildingId.empty())
     * ENSURE(isProperlyInitialized())
     * ENSURE(getName() == name)
     * ENSURE(getIdentifier() == id)
     * ENSURE(getCapacity() == capacity)
     * ENSURE(getCampusId() == campusId)
     * ENSURE(getBuildingId() == buildingId)
     */
    Room(const std::string& name,
         const std::string& id,
         int capacity,
         const std::string& campusId,
         const std::string& buildingId);

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
     * ENSURE(result > 0)
     */
    int getCapacity() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    const std::string& getCampusId() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    const std::string& getBuildingId() const;
};

#endif