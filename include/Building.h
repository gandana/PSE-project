#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include "DesignByContract.h"

class Building {
private:
    std::string fName;
    std::string fIdentifier;
    std::string fCampusId; // Verwijzing naar de Campus identifier
    bool fProperlyInitialized;

public:
    Building(const std::string& name, const std::string& id, const std::string& campusId);
    bool isProperlyInitialized() const;
    const std::string& getName() const;
    const std::string& getIdentifier() const;
    const std::string& getCampusId() const;
};

#endif