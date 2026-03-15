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

    // Linking a user to an existing meeting
    bool addParticipation(const std::string& meetingId, const std::string& userName) {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        REQUIRE(!userName.empty(), "User name cannot be empty");

        for (auto& m : meetings) {
            if (m.getIdentifier() == meetingId) {
                m.addParticipant(userName);
                return true;
            }
        }
        std::cerr << "Error: Cannot add participant. Meeting ID " << meetingId << " not found.\n";
        return false;
    }

    // Use Case 1.3: Process a single meeting
    void processMeeting(const std::string& meetingId) {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");

        Meeting* targetMeeting = nullptr;
        // Find the meeting
        for (auto& m : meetings) {
            if (m.getIdentifier() == meetingId) {
                targetMeeting = &m;
                break;
            }
        }

        if (!targetMeeting || targetMeeting->isProcessed() || targetMeeting->isCanceled()) {
            return; // Meeting doesn't exist or is already handled
        }

        // Checking for conflicts
        for (const auto& other : meetings) {
            if (other.isProcessed() && !other.isCanceled() &&
                other.getRoomId() == targetMeeting->getRoomId() &&
                other.getDate() == targetMeeting->getDate()) {

                // Exception triggered! Room is occupied.
                std::cerr << "Error: Room " << targetMeeting->getRoomId()
                          << " is already occupied on this date! Canceling meeting "
                          << targetMeeting->getIdentifier() << ".\n";
                targetMeeting->setCanceled(true);
                return;
            }
        }

        // Happy Day Scenario
        targetMeeting->setProcessed(true);
        std::cout << "Meeting " << targetMeeting->getIdentifier()
                  << " (" << targetMeeting->getLabel() << ") successfully processed.\n";
    }

    // Automatically process all meetings
    void processAllMeetings() {
        REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
        std::cout << "\n--- Starting Automatic Processing ---\n";

        for (auto& m : meetings) {
            // Only process if it hasn't been handled yet
            if (!m.isProcessed() && !m.isCanceled()) {
                processMeeting(m.getIdentifier());
            }
        }
        std::cout << "--- Processing Complete ---\n";
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