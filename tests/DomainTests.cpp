#include <gtest/gtest.h>
#include "../include/Room.h"
#include "../include/Meeting.h"
#include <chrono>

// --- ROOM TESTS ---

TEST(RoomTest, ValidRoomCreation) {
    Room r("M.G.025", "Room_1", 55);
    EXPECT_EQ(r.getName(), "M.G.025");
    EXPECT_EQ(r.getIdentifier(), "Room_1");
    EXPECT_EQ(r.getCapacity(), 55);
    EXPECT_TRUE(r.isProperlyInitialized());
}

TEST(RoomTest, InvalidCapacityTriggersContract) {
    EXPECT_DEATH(Room("BadRoom", "Room_Bad", 0), "Capacity must be strictly greater than 0");
}

TEST(RoomTest, EmptyNameTriggersContract) {
    EXPECT_DEATH(Room("", "Room_Bad", 10), "Name cannot be empty");
}

// --- MEETING TESTS ---
// Ik heb de naam veranderd naar MeetingDomainTest om conflicten met TEST_F in andere bestanden te voorkomen

TEST(MeetingDomainTest, ValidMeetingCreation) {
    auto now = std::chrono::system_clock::now();
    Meeting m("Weekly Sync", "Meet_1", "Room_1", now);

    EXPECT_EQ(m.getLabel(), "Weekly Sync");
    EXPECT_EQ(m.getIdentifier(), "Meet_1");
    EXPECT_EQ(m.getRoomId(), "Room_1");
    EXPECT_FALSE(m.isProcessed());
    EXPECT_FALSE(m.isCanceled());
}

TEST(MeetingDomainTest, AddParticipant) {
    auto now = std::chrono::system_clock::now();
    Meeting m("Weekly Sync", "Meet_1", "Room_1", now);

    m.addParticipant("Serge Demeyer");
    ASSERT_EQ(m.getParticipants().size(), 1);
    EXPECT_EQ(m.getParticipants()[0], "Serge Demeyer");
}

TEST(MeetingDomainTest, EmptyParticipantTriggersContract) {
    auto now = std::chrono::system_clock::now();
    Meeting m("Weekly Sync", "Meet_1", "Room_1", now);
    
    EXPECT_DEATH(m.addParticipant(""), "User name cannot be empty");
}

TEST(MeetingDomainTest, EmptyMeetingIdTriggersContract) {
    auto now = std::chrono::system_clock::now();
    EXPECT_DEATH(Meeting("Label", "", "Room1", now), "Identifier cannot be empty");
}

TEST(MeetingDomainTest, EmptyRoomIdTriggersContract) {
    auto now = std::chrono::system_clock::now();
    EXPECT_DEATH(Meeting("Label", "ID1", "", now), "Room ID cannot be empty");
}