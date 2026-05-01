#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "DesignByContract.h"

/**
 * @class Room
 * @brief Representeert een kamer op de campus met een specifieke capaciteit.
 */
class Room {
private:
    std::string fName;
    std::string fIdentifier;
    int fCapacity;
    bool fProperlyInitialized;

public:
    /**
     * @brief Constructor voor een Room object.
     * @param name De menselijk leesbare naam van de kamer.
     * @param id De unieke identifier van de kamer.
     * @param capacity Het aantal mensen dat in de kamer past (moet > 0 zijn).
     */
    Room(const std::string& name, const std::string& id, int capacity);

    /**
     * @brief Controleert of het object correct is geïnitialiseerd.
     */
    bool isProperlyInitialized() const;

    // --- Getters ---
    const std::string& getName() const;
    const std::string& getIdentifier() const;
    int getCapacity() const;
};

#endif // ROOM_H