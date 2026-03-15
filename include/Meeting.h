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
    std::vector<std::string> participants;
    bool properlyInitialized;

    // Tracking variables for Use Cases 1.3 & 1.4
    bool processed;
    bool canceled;

public:
    Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d)
        : label(lbl), identifier(id), roomId(rId), date(d), properlyInitialized(true), processed(false), canceled(false) {

        REQUIRE(!lbl.empty(), "Label cannot be empty");
        REQUIRE(!id.empty(), "Identifier cannot be empty");
        REQUIRE(!rId.empty(), "Room ID cannot be empty");
        ENSURE(isProperlyInitialized(), "Meeting was not properly initialized");
    }

    bool isProperlyInitialized() const { return properlyInitialized; }

    void addParticipant(const std::string& userName) {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        REQUIRE(!userName.empty(), "User name cannot be empty");
        participants.push_back(userName);
    }

    // Setters & Getters
    void setProcessed(bool status) { processed = status; }
    bool isProcessed() const { return processed; }

    void setCanceled(bool status) { canceled = status; }
    bool isCanceled() const { return canceled; }

    // Standard Getters
    const std::string& getLabel() const { return label; }
    const std::string& getIdentifier() const { return identifier; }
    const std::string& getRoomId() const { return roomId; }
    std::chrono::system_clock::time_point getDate() const { return date; }
    const std::vector<std::string>& getParticipants() const { return participants; }
};

#endif // MEETING_H