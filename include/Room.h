#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "DesignByContract.h"

class Room {
private:
    std::string name;
    std::string identifier;
    int capacity;
    bool properlyInitialized;

public:
    // Constructor with Preconditions
    Room(const std::string& n, const std::string& id, int cap) : name(n), identifier(id), capacity(cap) {
        REQUIRE(!n.empty(), "Name cannot be empty");
        REQUIRE(!id.empty(), "Identifier cannot be empty");
        REQUIRE(cap > 0, "Capacity must be strictly greater than 0");
        
        properlyInitialized = true;
        ENSURE(isProperlyInitialized(), "Room was not properly initialized");
    }

    bool isProperlyInitialized() const { return properlyInitialized; }

    // Getters with Postconditions 
    const std::string& getName() const {
        REQUIRE(isProperlyInitialized(), "Room not initialized");
        return name;
    }

    const std::string& getIdentifier() const {
        REQUIRE(isProperlyInitialized(), "Room not initialized");
        return identifier;
    }

    int getCapacity() const {
        REQUIRE(isProperlyInitialized(), "Room not initialized");
        return capacity;
    }
};

#endif