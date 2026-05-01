#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "DesignByContract.h"

/**
 * @class Room
 * @brief Vertegenwoordigt een fysieke kamer in het vergadersysteem.
 * * Deze klasse bevat de basisgegevens van een kamer, zoals de naam,
 * unieke identifier en de maximale capaciteit.
 */
class Room {
private:
    std::string name;
    std::string identifier;
    int capacity;
    bool properlyInitialized;

public:
    /**
     * @brief Constructor voor een Room.
     * @param n De weergavenaam van de kamer.
     * @param id De unieke identifier van de kamer.
     * @param cap De maximale capaciteit van de kamer (moet > 0 zijn).
     * @pre n mag niet leeg zijn.
     * @pre id mag niet leeg zijn.
     * @pre cap moet strikt groter dan 0 zijn.
     * @post Het object is correct geïnitialiseerd.
     */
    Room(const std::string& n, const std::string& id, int cap)
        : name(n), identifier(id), capacity(cap), properlyInitialized(true) {
        REQUIRE(!n.empty(), "Name cannot be empty");
        REQUIRE(!id.empty(), "Identifier cannot be empty");
        REQUIRE(cap > 0, "Capacity must be strictly greater than 0");
        ENSURE(isProperlyInitialized(), "Room was not properly initialized");
    }

    /**
     * @brief Controleert of het object correct is aangemaakt.
     * @return true als de kamer correct is geïnitialiseerd, anders false.
     */
    bool isProperlyInitialized() const { return properlyInitialized; }

    const std::string& getName() const { return name; }
    const std::string& getIdentifier() const { return identifier; }
    int getCapacity() const { return capacity; }
};

#endif // ROOM_H