#include "Meeting.h"

// --- Constructor ---
Meeting::Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d)
    : fLabel(lbl), fIdentifier(id), fRoomId(rId), fDate(d), fProperlyInitialized(true), fProcessed(false), fCanceled(false) {

    // Design by Contract: Precondities
    REQUIRE(!lbl.empty(), "Label cannot be empty");
    REQUIRE(!id.empty(), "Identifier cannot be empty");
    REQUIRE(!rId.empty(), "Room ID cannot be empty");

    // Design by Contract: Postconditie
    ENSURE(isProperlyInitialized(), "Meeting was not properly initialized");
}

bool Meeting::isProperlyInitialized() const {
    return fProperlyInitialized;
}

// --- Getters ---
const std::string& Meeting::getLabel() const {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    return fLabel;
}

const std::string& Meeting::getIdentifier() const {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    return fIdentifier;
}

const std::string& Meeting::getRoomId() const {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    return fRoomId;
}

std::chrono::system_clock::time_point Meeting::getDate() const {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    return fDate;
}

const std::vector<std::string>& Meeting::getParticipants() const {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    return fParticipants;
}

bool Meeting::isProcessed() const {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    return fProcessed;
}

bool Meeting::isCanceled() const {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    return fCanceled;
}

// --- Setters & Actions ---

void Meeting::addParticipant(const std::string& userName) {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    REQUIRE(!userName.empty(), "User name cannot be empty");

    unsigned int oldSize = fParticipants.size();
    fParticipants.push_back(userName);

    // Postconditie om te checken of de vector echt gegroeid is
    ENSURE(fParticipants.size() == oldSize + 1, "Participant was not added correctly");
}

void Meeting::setProcessed(bool status) {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    fProcessed = status;
    ENSURE(isProcessed() == status, "Processed status not set correctly");
}

void Meeting::setCanceled(bool status) {
    REQUIRE(isProperlyInitialized(), "Meeting not initialized");
    fCanceled = status;
    ENSURE(isCanceled() == status, "Canceled status not set correctly");
}