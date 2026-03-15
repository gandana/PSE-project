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
    // Tests that a capacity of 0 violates the REQUIRE contract
    EXPECT_DEATH(Room("BadRoom", "Room_Bad", 0), "Capacity must be strictly greater than 0");
}

TEST(RoomTest, EmptyNameTriggersContract) {
    // Tests that an empty name violates the REQUIRE contract
    EXPECT_DEATH(Room("", "Room_Bad", 10), "Name cannot be empty");
}

// --- MEETING TESTS ---

TEST(MeetingTest, ValidMeetingCreation) {
    auto now = std::chrono::system_clock::now();
    Meeting m("Weekly Sync", "Meet_1", "Room_1", now);
    
    EXPECT_EQ(m.getLabel(), "Weekly Sync");
    EXPECT_EQ(m.getIdentifier(), "Meet_1");
    EXPECT_EQ(m.getRoomId(), "Room_1");
    EXPECT_FALSE(m.isProcessed());
    EXPECT_FALSE(m.isCanceled());
}

TEST(MeetingTest, AddParticipant) {
    auto now = std::chrono::system_clock::now();
    Meeting m("Weekly Sync", "Meet_1", "Room_1", now);
    
    m.addParticipant("Serge Demeyer");
    ASSERT_EQ(m.getParticipants().size(), 1);
    EXPECT_EQ(m.getParticipants()[0], "Serge Demeyer");
}

TEST(MeetingTest, EmptyParticipantTriggersContract) {
    auto now = std::chrono::system_clock::now();
    Meeting m("Weekly Sync", "Meet_1", "Room_1", now);
    
    EXPECT_DEATH(m.addParticipant(""), "User name cannot be empty");
}