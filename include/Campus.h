#ifndef CAMPUS_H
#define CAMPUS_H

#include <string>
#include "DesignByContract.h"

class Campus {
private:
    std::string fName;
    std::string fIdentifier;
    bool fProperlyInitialized;

public:

    /**
     * REQUIRE(!name.empty())
     * REQUIRE(!id.empty())
     * ENSURE(isProperlyInitialized())
     * ENSURE(getName() == name)
     * ENSURE(getIdentifier() == id)
     */
    Campus(const std::string& name, const std::string& id);

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
};

#endif