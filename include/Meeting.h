#ifndef MEETING_H
#define MEETING_H

#include <string>
#include <chrono>
#include <vector>
#include "DesignByContract.h"

class Meeting {
private:
    std::string label;
    std::string identifier;
    std::string roomId;
    std::chrono::system_clock::time_point date;
    std::vector<std::string> participants; // To hold user names
    bool properlyInitialized;

public:
    // Constructor
    Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d)
        : label(lbl), identifier(id), roomId(rId), date(d), properlyInitialized(true) {

        REQUIRE(!lbl.empty(), "Label cannot be empty");
        REQUIRE(!id.empty(), "Identifier cannot be empty");
        REQUIRE(!rId.empty(), "Room ID cannot be empty");

        ENSURE(isProperlyInitialized(), "Meeting was not properly initialized");
    }

    bool isProperlyInitialized() const { return properlyInitialized; }

    // Method to add a participant
    void addParticipant(const std::string& userName) {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        REQUIRE(!userName.empty(), "User name cannot be empty"); // User cannot be empty (spec)

        participants.push_back(userName);

        ENSURE(participants.back() == userName, "Participant was not added properly");
    }

    // Getters
    const std::string& getLabel() const { REQUIRE(isProperlyInitialized(), "Meeting not initialized"); return label; }
    const std::string& getIdentifier() const { REQUIRE(isProperlyInitialized(), "Meeting not initialized"); return identifier; }
    const std::string& getRoomId() const { REQUIRE(isProperlyInitialized(), "Meeting not initialized"); return roomId; }
    std::chrono::system_clock::time_point getDate() const { REQUIRE(isProperlyInitialized(), "Meeting not initialized"); return date; }

    // Getter for participants
    const std::vector<std::string>& getParticipants() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return participants;
    }
};

#endif // MEETING_H