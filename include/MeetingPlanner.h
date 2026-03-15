#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

#include <vector>
#include <iostream>
#include "Room.h"
#include "Meeting.h"
#include "DesignByContract.h"

/**
 * @class MeetingPlanner
 * @brief Beheert alle kamers en vergaderingen in het systeem.
 * * Dit is de centrale klasse (het hart van het domein) die verantwoordelijk is
 * voor het opslaan van de data en het verwerken van de simulatie om dubbele
 * boekingen te voorkomen.
 */
class MeetingPlanner {
private:
    std::vector<Room> rooms;
    std::vector<Meeting> meetings;
    bool properlyInitialized;

public:
    MeetingPlanner() : properlyInitialized(true) {
        ENSURE(isProperlyInitialized(), "MeetingPlanner not properly initialized");
    }

    bool isProperlyInitialized() const { return properlyInitialized; }

    void addRoom(const Room& room) { rooms.push_back(room); }
    void addMeeting(const Meeting& meeting) { meetings.push_back(meeting); }
    /**
         * @brief Koppelt een gebruiker aan een bestaande meeting.
         * @param meetingId De ID van de meeting waar de gebruiker bij hoort.
         * @param userName De naam van de deelnemer.
         */
    void addParticipation(const std::string& meetingId, const std::string& userName) {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");

        // Zoek de juiste meeting op basis van de ID
        for (auto& m : meetings) {
            if (m.getIdentifier() == meetingId) {
                m.addParticipant(userName); // Gebruikt de functie uit je Meeting.h
                return;
            }
        }
        // Als de meeting niet wordt gevonden
        std::cerr << "Warning: Meeting " << meetingId << " not found for user " << userName << std::endl;
    }
    const std::vector<Room>& getRooms() const { return rooms; }
    const std::vector<Meeting>& getMeetings() const { return meetings; }

    /**
     * @brief Verwerkt een specifieke vergadering en checkt op conflicten.
     * * Zoekt de vergadering en controleert of de kamer op die datum al bezet is.
     * Zo ja, dan wordt de vergadering geannuleerd. Zo nee, dan wordt deze verwerkt.
     * @param meetingId De ID van de te verwerken vergadering.
     * @pre De planner moet correct geïnitialiseerd zijn.
     * @post De status van de meeting is 'processed' (succes) of 'canceled' (conflict).
     */
    void processMeeting(const std::string& meetingId) {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");

        Meeting* targetMeeting = nullptr;
        for (auto& m : meetings) {
            if (m.getIdentifier() == meetingId) {
                targetMeeting = &m;
                break;
            }
        }

        if (!targetMeeting || targetMeeting->isProcessed() || targetMeeting->isCanceled()) {
            return;
        }

        for (const auto& other : meetings) {
            if (other.isProcessed() && !other.isCanceled() &&
                other.getRoomId() == targetMeeting->getRoomId() &&
                other.getDate() == targetMeeting->getDate()) {

                std::cerr << "Error: Room " << targetMeeting->getRoomId()
                          << " is already occupied on this date! Canceling meeting "
                          << targetMeeting->getIdentifier() << ".\n";
                targetMeeting->setCanceled(true);
                return;
            }
        }

        targetMeeting->setProcessed(true);
        std::cout << "Meeting " << targetMeeting->getIdentifier()
                  << " (" << targetMeeting->getLabel() << ") successfully processed.\n";
    }

    /**
     * @brief Doorloopt en verwerkt alle niet-verwerkte vergaderingen in het systeem.
     * @pre De planner moet correct geïnitialiseerd zijn.
     */
    void processAllMeetings() {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        std::cout << "\n--- Starting Automatic Processing ---\n";

        for (auto& m : meetings) {
            if (!m.isProcessed() && !m.isCanceled()) {
                processMeeting(m.getIdentifier());
            }
        }
        std::cout << "--- Processing Complete ---\n";
    }
};

#endif // MEETINGPLANNER_H