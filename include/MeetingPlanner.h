#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

#include <vector>
#include <string>
#include "Room.h"
#include "Meeting.h"
#include "DesignByContract.h"

/**
 * @class MeetingPlanner
 * @brief Beheert de kamers en vergaderingen en voert de simulatie uit.
 */
class MeetingPlanner {
private:
    std::vector<Room> rooms;
    std::vector<Meeting> meetings;
    bool properlyInitialized;

public:
    /**
     * @brief Constructor voor de MeetingPlanner.
     */
    MeetingPlanner();

    /**
     * @brief Controleert of de planner correct is geïnitialiseerd.
     */
    bool isProperlyInitialized() const;

    // --- Data Management ---
    void addRoom(const Room& room);
    void addMeeting(const Meeting& meeting);
    void addParticipation(const std::string& meetingId, const std::string& userName);

    // --- Getters ---
    const std::vector<Room>& getRooms() const;
    const std::vector<Meeting>& getMeetings() const;

    // --- Simulatie Logica ---
    /**
     * @brief Verwerkt één specifieke meeting en controleert op conflicten.
     */
    void processMeeting(const std::string& meetingId);

    /**
     * @brief Verwerkt automatisch alle meetings in het systeem.
     */
    void processAllMeetings();
};

#endif // MEETINGPLANNER_H