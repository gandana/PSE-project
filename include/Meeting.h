#ifndef MEETING_H
#define MEETING_H

#include <string>
#include <chrono>
#include <vector>
#include "DesignByContract.h"

/**
 * @class Meeting
 * @brief Vertegenwoordigt een ingeplande vergadering.
 * * Slaat de gegevens op van een vergadering, inclusief de deelnemers, de toegewezen
 * kamer, en houdt bij of de vergadering succesvol is verwerkt of geannuleerd.
 */
class Meeting {
private:
    std::string label;
    std::string identifier;
    std::string roomId;
    std::chrono::system_clock::time_point date;
    std::vector<std::string> participants;
    bool properlyInitialized;
    bool processed;
    bool canceled;

public:
    /**
     * @brief Constructor voor een Meeting.
     * @param lbl De weergavenaam of het onderwerp van de vergadering.
     * @param id De unieke identifier van de vergadering.
     * @param rId De unieke identifier van de kamer waar de vergadering plaatsvindt.
     * @param d De datum van de vergadering.
     * @pre lbl, id, en rId mogen niet leeg zijn.
     * @post Het object is correct geïnitialiseerd en de statussen staan op false.
     */
    Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d)
        : label(lbl), identifier(id), roomId(rId), date(d), properlyInitialized(true), processed(false), canceled(false) {
        REQUIRE(!lbl.empty(), "Label cannot be empty");
        REQUIRE(!id.empty(), "Identifier cannot be empty");
        REQUIRE(!rId.empty(), "Room ID cannot be empty");
        ENSURE(isProperlyInitialized(), "Meeting was not properly initialized");
    }

    bool isProperlyInitialized() const { return properlyInitialized; }

    /**
     * @brief Voegt een deelnemer toe aan de vergadering.
     * @param userName De naam van de deelnemer.
     * @pre De naam van de deelnemer mag niet leeg zijn.
     */
    void addParticipant(const std::string& userName) {
        REQUIRE(isProperlyInitialized(), "Meeting not initialized");
        REQUIRE(!userName.empty(), "User name cannot be empty");
        participants.push_back(userName);
    }

    void setProcessed(bool status) { processed = status; }
    bool isProcessed() const { return processed; }

    void setCanceled(bool status) { canceled = status; }
    bool isCanceled() const { return canceled; }

    const std::string& getLabel() const { return label; }
    const std::string& getIdentifier() const { return identifier; }
    const std::string& getRoomId() const { return roomId; }
    std::chrono::system_clock::time_point getDate() const { return date; }
    const std::vector<std::string>& getParticipants() const { return participants; }
};

#endif // MEETING_H