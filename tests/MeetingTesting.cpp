#include <gtest/gtest.h>
#include "Meeting.h"
#include <chrono>

class MeetingTest : public ::testing::Test {
protected:
    std::chrono::system_clock::time_point testDate =
            std::chrono::system_clock::now();
};

TEST_F(MeetingTest, ConstructorAndGetters) {
    Meeting meeting("Project Overleg", "M001", "Room_A", testDate);

    EXPECT_EQ(meeting.getLabel(), "Project Overleg");
    EXPECT_EQ(meeting.getIdentifier(), "M001");
    EXPECT_EQ(meeting.getRoomId(), "Room_A");
    EXPECT_TRUE(meeting.isProperlyInitialized());
    EXPECT_FALSE(meeting.isProcessed());
    EXPECT_FALSE(meeting.isCanceled());
}

TEST_F(MeetingTest, AddParticipants) {
    Meeting meeting("Overleg", "M001", "Room_A", testDate);

    meeting.addParticipant("Kasper");
    meeting.addParticipant("Denys");

    EXPECT_EQ(meeting.getParticipants().size(), 2);
    EXPECT_EQ(meeting.getParticipants()[0], "Kasper");
    EXPECT_EQ(meeting.getParticipants()[1], "Denys");
}

TEST_F(MeetingTest, StatusUpdates) {
    Meeting meeting("Overleg", "M001", "Room_A", testDate);

    meeting.setProcessed(true);
    EXPECT_TRUE(meeting.isProcessed());

    meeting.setCanceled(true);
    EXPECT_TRUE(meeting.isCanceled());
}

TEST_F(MeetingTest, EmptyLabelDies) {
    EXPECT_DEATH(Meeting("", "ID", "ROOM", testDate),
                 "Label cannot be empty");
}

TEST_F(MeetingTest, EmptyIdentifierDies) {
    EXPECT_DEATH(Meeting("Overleg", "", "ROOM", testDate),
                 "Identifier cannot be empty");
}

TEST_F(MeetingTest, EmptyRoomDies) {
    EXPECT_DEATH(Meeting("Overleg", "ID", "", testDate),
                 "Room ID cannot be empty");
}

TEST_F(MeetingTest, EmptyParticipantDies) {
    Meeting meeting("Overleg", "M001", "Room_A", testDate);

    EXPECT_DEATH(meeting.addParticipant(""),
                 "User name cannot be empty");
}