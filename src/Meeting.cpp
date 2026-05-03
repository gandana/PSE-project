#include "Meeting.h"

Meeting::Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d)
    : fIsOnline(false),             // Use Case 3.4
      fAllowsExternals(false),      // Use Case 3.7
      fExternalCount(0),            // Use Case 3.5
      fLabel(lbl),
      fIdentifier(id),
      fRoomId(rId),
      fDate(d),
      fProperlyInitialized(false),
      fProcessed(false),
      fCanceled(false)
{
    // De REQUIREMENTS (Design by Contract) zijn verplicht voor je punten![cite: 1]
    REQUIRE(!lbl.empty(), "Label cannot be empty");
    REQUIRE(!id.empty(), "Identifier cannot be empty");
    // Let op: als de meeting ONLINE is, mag rId leeg zijn volgens Use Case 3.4[cite: 1]
    // Maar bij het inladen via de constructor laten we de check vaak staan.

    fProperlyInitialized = true;
    ENSURE(isProperlyInitialized(), "Meeting not properly initialized");
}
bool Meeting::isProperlyInitialized() const {
    return fProperlyInitialized;
}

void Meeting::addParticipant(const std::string& userName, bool isExternal) {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    // Belangrijk voor de test en Use Case 1.1: USER mag niet leeg zijn
    REQUIRE(!userName.empty(), "User name cannot be empty");

    fParticipants.push_back(userName);

    // Use Case 3.5 & 3.7: Als de gebruiker extern is, tellen we dit op voor de CO2
    if (isExternal) {
        fExternalCount++;
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
}

void Meeting::setCanceled(bool status) {
    REQUIRE(isProperlyInitialized(), "Meeting not properly initialized");
    fCanceled = status;
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
