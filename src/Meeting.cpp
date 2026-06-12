#include "Meeting.h"

Meeting::Meeting(const std::string& lbl,
                 const std::string& id,
                 const std::string& rId,
                 std::chrono::system_clock::time_point d)
    : fIsOnline(false),
      fAllowsExternals(false),
      fExternalCount(0),
      fLabel(lbl),
      fIdentifier(id),
      fRoomId(rId),
      fDate(d),
      fProperlyInitialized(false),
      fProcessed(false),
      fCanceled(false)
{
    REQUIRE(!lbl.empty(), "Label cannot be empty");
    REQUIRE(!id.empty(), "Identifier cannot be empty");
    REQUIRE(!rId.empty(), "Room ID cannot be empty");

    fProperlyInitialized = true;

    ENSURE(isProperlyInitialized(), "Meeting not properly initialized");
    ENSURE(fLabel == lbl, "Label was not set correctly");
    ENSURE(fIdentifier == id, "Identifier was not set correctly");
    ENSURE(fRoomId == rId, "Room ID was not set correctly");
    ENSURE(!fProcessed, "Meeting should not be processed initially");
    ENSURE(!fCanceled, "Meeting should not be canceled initially");
    ENSURE(fParticipants.empty(), "Meeting should start with no participants");
}
bool Meeting::isProperlyInitialized() const {
    return fProperlyInitialized;
}

void Meeting::addParticipant(const std::string& userName, bool isExternal) {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    REQUIRE(!userName.empty(), "User name cannot be empty");

    size_t oldSize = fParticipants.size();
    int oldExternalCount = fExternalCount;

    fParticipants.push_back(userName);

    if (isExternal) {
        fExternalCount++;
    }

    ENSURE(fParticipants.size() == oldSize + 1, "Participant was not added");
    ENSURE(fParticipants.back() == userName, "Wrong participant added");

    if (isExternal) {
        ENSURE(fExternalCount == oldExternalCount + 1, "External count was not updated");
    } else {
        ENSURE(fExternalCount == oldExternalCount, "External count changed incorrectly");
    }
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

    ENSURE(fProcessed == status,
           "Processed status not set correctly");
}

void Meeting::setCanceled(bool status) {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");

    fCanceled = status;

    ENSURE(fCanceled == status,
           "Canceled status not set correctly");
}
double Meeting::calculateCO2() const {
    REQUIRE(isProperlyInitialized(), "Meeting niet geinitialiseerd");

    double totalCO2 = 0.0;
    int totalParticipants = fParticipants.size();

    if (fIsOnline) {
        // Online: 30g per deelnemer
        totalCO2 = totalParticipants * 30.0;
    } else {
        // Fysiek: 1200g voor externen, 120g voor internen
        int internalCount = totalParticipants - fExternalCount;
        totalCO2 = (fExternalCount * 1200.0) + (internalCount * 120.0);
    }

    return totalCO2;
}
void Meeting::setOnline(bool online) {
    REQUIRE(isProperlyInitialized(), "Meeting niet geïnitialiseerd");
    fIsOnline = online;
}

bool Meeting::isOnline() const {
    REQUIRE(isProperlyInitialized(), "Meeting niet geïnitialiseerd");
    return fIsOnline;
}
int Meeting::getParticipantCount() const {
    REQUIRE(isProperlyInitialized(), "Meeting niet geïnitialiseerd");
    return (int)fParticipants.size();
}
std::string Meeting::getDateString() const {
    REQUIRE(isProperlyInitialized(), "Meeting niet geïnitialiseerd");

    std::time_t t = std::chrono::system_clock::to_time_t(fDate);
    std::tm* tm_ptr = std::localtime(&t);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_ptr);
    return std::string(buffer);
}