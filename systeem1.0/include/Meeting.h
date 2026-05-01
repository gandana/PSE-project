#ifndef INC_MEETING_H
#define INC_MEETING_H

#include <string>
#include <chrono>
#include <vector>
#include "DesignByContract.h"

class Meeting {
private:
    std::string fLabel;
    std::string fIdentifier;
    std::string fRoomId;
    std::chrono::system_clock::time_point fDate;
    std::vector<std::string> fParticipants;
    bool fProperlyInitialized;
    bool fProcessed;
    bool fCanceled;

public:
    /**
     * @brief Constructor voor een Meeting object.
     * REQUIRE(!lbl.empty(), "Label mag niet leeg zijn");
     * REQUIRE(!id.empty(), "Identifier mag niet leeg zijn");
     * REQUIRE(!rId.empty(), "Room ID mag niet leeg zijn");
     * ENSURE(isProperlyInitialized(), "Meeting moet correct geïnitialiseerd zijn");
     */
    Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d)
        : fLabel(lbl), fIdentifier(id), fRoomId(rId), fDate(d), fProperlyInitialized(true), fProcessed(false), fCanceled(false) {
        REQUIRE(!lbl.empty(), "Label cannot be empty");
        REQUIRE(!id.empty(), "Identifier cannot be empty");
        REQUIRE(!rId.empty(), "Room ID cannot be empty");
        ENSURE(isProperlyInitialized(), "Meeting was not properly initialized");
    }

    bool isProperlyInitialized() const {
        return fProperlyInitialized;
    }

    // --- GETTERS ---

    const std::string& getLabel() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return fLabel;
    }

    const std::string& getIdentifier() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return fIdentifier;
    }

    const std::string& getRoomId() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return fRoomId;
    }

    std::chrono::system_clock::time_point getDate() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return fDate;
    }

    const std::vector<std::string>& getParticipants() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return fParticipants;
    }

    bool isProcessed() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return fProcessed;
    }

    bool isCanceled() const {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        return fCanceled;
    }

    // --- SETTERS & ACTIONS ---

    void addParticipant(const std::string& userName) {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        REQUIRE(!userName.empty(), "User name cannot be empty");
        unsigned int oldSize = fParticipants.size();

        fParticipants.push_back(userName);

        ENSURE(fParticipants.size() == oldSize + 1, "Participant was not added correctly");
    }

    void setProcessed(bool status) {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        fProcessed = status;
        ENSURE(isProcessed() == status, "Processed status not set correctly");
    }

    void setCanceled(bool status) {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        fCanceled = status;
        ENSURE(isCanceled() == status, "Canceled status not set correctly");
    }
};

#endif // INC_MEETING_H