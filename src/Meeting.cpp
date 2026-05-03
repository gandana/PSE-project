#include "Meeting.h"

Meeting::Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d)
    : fLabel(lbl), fIdentifier(id), fRoomId(rId), fDate(d),
      fProperlyInitialized(false), fProcessed(false), fCanceled(false) {

    // De test verwacht deze specifieke teksten:
    REQUIRE(!id.empty(), "Identifier cannot be empty");
    REQUIRE(!rId.empty(), "Room ID cannot be empty");

    fProperlyInitialized = true;
    ENSURE(isProperlyInitialized(), "Meeting not properly initialized");
}

bool Meeting::isProperlyInitialized() const {
    return fProperlyInitialized;
}

void Meeting::addParticipant(const std::string& userName) {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    // Belangrijk voor de test:
    REQUIRE(!userName.empty(), "User name cannot be empty");

    fParticipants.push_back(userName);
}

// Getters
const std::string& Meeting::getLabel() const {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    return fLabel;
}

const std::string& Meeting::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    return fIdentifier;
}

const std::string& Meeting::getRoomId() const {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    return fRoomId;
}

std::chrono::system_clock::time_point Meeting::getDate() const {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    return fDate;
}

const std::vector<std::string>& Meeting::getParticipants() const {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    return fParticipants;
}

bool Meeting::isProcessed() const {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    return fProcessed;
}

bool Meeting::isCanceled() const {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    return fCanceled;
}

void Meeting::setProcessed(bool status) {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    fProcessed = status;
}

void Meeting::setCanceled(bool status) {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    fCanceled = status;
}