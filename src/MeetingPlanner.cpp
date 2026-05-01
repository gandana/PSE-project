#include "../include/MeetingPlanner.h"
#include <iostream>

MeetingPlanner::MeetingPlanner() : properlyInitialized(true) {
    ENSURE(isProperlyInitialized(), "MeetingPlanner not properly initialized");
}

bool MeetingPlanner::isProperlyInitialized() const {
    return properlyInitialized;
}

void MeetingPlanner::addRoom(const Room& room) {
    REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
    rooms.push_back(room);
}

void MeetingPlanner::addMeeting(const Meeting& meeting) {
    REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
    meetings.push_back(meeting);
}

void MeetingPlanner::addParticipation(const std::string& meetingId, const std::string& userName) {
    REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");

    for (auto& m : meetings) {
        if (m.getIdentifier() == meetingId) {
            m.addParticipant(userName);
            return;
        }
    }
    std::cerr << "Warning: Meeting " << meetingId << " not found for user " << userName << std::endl;
}

const std::vector<Room>& MeetingPlanner::getRooms() const {
    REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
    return rooms;
}

const std::vector<Meeting>& MeetingPlanner::getMeetings() const {
    REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
    return meetings;
}

void MeetingPlanner::processMeeting(const std::string& meetingId) {
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

    // 1. Check op Kamer-bezetting (Dubbele boeking)
    for (const auto& other : meetings) {
        if (other.isProcessed() && !other.isCanceled() &&
            other.getRoomId() == targetMeeting->getRoomId() &&
            other.getDate() == targetMeeting->getDate()) {

            std::cerr << "Error: Room " << targetMeeting->getRoomId()
                      << " is already occupied! Canceling " << targetMeeting->getIdentifier() << ".\n";
            targetMeeting->setCanceled(true);
            return;
        }
    }

    // 2. Check op Capaciteit (Appendix B)
    const Room* roomPtr = nullptr;
    for (const auto& r : rooms) {
        if (r.getIdentifier() == targetMeeting->getRoomId()) {
            roomPtr = &r;
            break;
        }
    }

    if (roomPtr && targetMeeting->getParticipants().size() > (size_t)roomPtr->getCapacity()) {
        std::cerr << "Error: Room " << roomPtr->getName() << " has insufficient capacity!\n";
        targetMeeting->setCanceled(true);
        return;
    }

    // Als alles goed is: verwerken
    targetMeeting->setProcessed(true);
    std::cout << "Meeting " << targetMeeting->getIdentifier() << " successfully processed.\n";
}

void MeetingPlanner::processAllMeetings() {
    REQUIRE(isProperlyInitialized(), "MeetingPlanner not initialized");
    std::cout << "\n--- Starting Automatic Processing ---\n";

    for (auto& m : meetings) {
        if (!m.isProcessed() && !m.isCanceled()) {
            processMeeting(m.getIdentifier());
        }
    }
    std::cout << "--- Processing Complete ---\n";
}