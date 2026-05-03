#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "DesignByContract.h"

class Room {
private:
    std::string fName;
    std::string fIdentifier;
    int fCapacity;
    std::string fCampusId;   // NIEUW: link naar Campus
    std::string fBuildingId; // NIEUW: link naar Building[cite: 1]
    bool fProperlyInitialized;

public:
    // Aangepaste constructor met campus en building[cite: 1]
    Room(const std::string& name, const std::string& id, int capacity,
         const std::string& campusId, const std::string& buildingId);

    bool isProperlyInitialized() const;

    const std::string& getName() const;
    const std::string& getIdentifier() const;
    int getCapacity() const;

    // Nieuwe getters voor de hiërarchie
    const std::string& getCampusId() const;
    const std::string& getBuildingId() const;
};

#endif