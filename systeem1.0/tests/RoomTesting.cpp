#include <gtest/gtest.h>
#include "Meeting.h"
#include <chrono>

class MeetingTest : public ::testing::Test {
protected:
    // Hulpvariabele voor een standaard datum (vandaag)
    std::chrono::system_clock::time_point testDate = std::chrono::system_clock::now();
};

// 1. Test de Constructor en Getters (Happy Day)
TEST_F(MeetingTest, ConstructorAndGetters) {
    Meeting meeting("Project Overleg", "M001", "Room_A", testDate);

    EXPECT_EQ(meeting.getLabel(), "Project Overleg");
    EXPECT_EQ(meeting.getIdentifier(), "M001");
    EXPECT_EQ(meeting.getRoomId(), "Room_A");
    EXPECT_TRUE(meeting.isProperlyInitialized());
    EXPECT_FALSE(meeting.isProcessed());
    EXPECT_FALSE(meeting.isCanceled());
}

// 2. Test het toevoegen van deelnemers
TEST_F(MeetingTest, AddParticipants) {
    Meeting meeting("Overleg", "M001", "Room_A", testDate);

    meeting.addParticipant("Kasper");
    meeting.addParticipant("Denys");

    EXPECT_EQ(meeting.getParticipants().size(), 2);
    EXPECT_EQ(meeting.getParticipants()[0], "Kasper");
    EXPECT_EQ(meeting.getParticipants()[1], "Denys");
}

// 3. Test de status wijzigingen
TEST_F(MeetingTest, StatusUpdates) {
    Meeting meeting("Overleg", "M001", "Room_A", testDate);

    meeting.setProcessed(true);
    EXPECT_TRUE(meeting.isProcessed());

    meeting.setCanceled(true);
    EXPECT_TRUE(meeting.isCanceled());
}

// 4. Test de CONTRACTEN (REQUIRE)
// Deze testen controleren of je programma inderdaad stopt bij foute input.
// Let op: gtest kan alleen ASSERT_DEATH gebruiken als je systeem abort() roept bij een contract_fail.
TEST_F(MeetingTest, ContractViolations) {
    // Test lege label in constructor (moet REQUIRE failen)
    EXPECT_DEATH(Meeting("", "ID", "ROOM", testDate), "Label cannot be empty");

    // Test lege deelnemer naam
    Meeting meeting("Overleg", "M001", "Room_A", testDate);
    EXPECT_DEATH(meeting.addParticipant(""), "User name cannot be empty");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}