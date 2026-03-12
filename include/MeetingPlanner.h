#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

#include <vector>
#include <string>
#include <iostream>
#include "Room.h"
#include "Meeting.h"
#include "DesignByContract.h"

class MeetingPlanner {
private:
    std::vector<Room> rooms;
    std::vector<Meeting> meetings;
    bool properlyInitialized;

public:
    MeetingPlanner() : properlyInitialized(true) {
        ENSURE(isProperlyInitialized(), "MeetingPlanner was not properly initialized");
    }

    bool isProperlyInitialized() const { return properlyInitialized; }

    // Add a room to the system
    void addRoom(const Room& room) {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        // Simple check to prevent duplicate Room IDs
        for (const auto& r : rooms) {
            if (r.getIdentifier() == room.getIdentifier()) {
                std::cerr << "Error: Room ID " << room.getIdentifier() << " already exists.\n";
                return;
            }
        }
        rooms.push_back(room);
        ENSURE(rooms.back().getIdentifier() == room.getIdentifier(), "Room was not added properly");
    }

    // Adding a meeting to the system
    void addMeeting(const Meeting& meeting) {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        // Check to prevent duplicate Meeting IDs
        for (const auto& m : meetings) {
            if (m.getIdentifier() == meeting.getIdentifier()) {
                std::cerr << "Error: Meeting ID " << meeting.getIdentifier() << " already exists.\n";
                return;
            }
        }
        meetings.push_back(meeting);
    }

    // Link a user to an existing meeting
    bool addParticipation(const std::string& meetingId, const std::string& userName) {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        REQUIRE(!userName.empty(), "User name cannot be empty");

        for (auto& m : meetings) {
            if (m.getIdentifier() == meetingId) {
                m.addParticipant(userName);
                return true; // Successfully added
            }
        }
        std::cerr << "Error: Cannot add participant. Meeting ID " << meetingId << " not found.\n";
        return false; // Meeting not found
    }

    // Getters for the parser and output classes
    const std::vector<Room>& getRooms() const {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        return rooms;
    }

    const std::vector<Meeting>& getMeetings() const {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        return meetings;
    }

    // Checking if a room exists
    bool roomExists(const std::string& roomId) const {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        for (const auto& r : rooms) {
            if (r.getIdentifier() == roomId) return true;
        }
        return false;
    }
};

#endif // MEETINGPLANNER_H