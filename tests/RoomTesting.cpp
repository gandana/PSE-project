#include <gtest/gtest.h>
#include "Room.h"

class RoomTest : public ::testing::Test {
};

// Happy day
TEST_F(RoomTest, ConstructorAndGetters) {
    Room room("Lokaal A", "R001", 30, "C001", "B001");

    EXPECT_TRUE(room.isProperlyInitialized());
    EXPECT_EQ(room.getName(), "Lokaal A");
    EXPECT_EQ(room.getIdentifier(), "R001");
    EXPECT_EQ(room.getCapacity(), 30);
    EXPECT_EQ(room.getCampusId(), "C001");
    EXPECT_EQ(room.getBuildingId(), "B001");
}

// Contract tests
TEST_F(RoomTest, InvalidCapacityDies) {
    EXPECT_DEATH(Room("Lokaal A", "R001", -5, "C001", "B001"),
                 "Capacity must be strictly greater than 0");
}

TEST_F(RoomTest, EmptyNameDies) {
    EXPECT_DEATH(Room("", "R001", 30, "C001", "B001"),
                 "Name cannot be empty");
}

TEST_F(RoomTest, EmptyIdentifierDies) {
    EXPECT_DEATH(Room("Lokaal A", "", 30, "C001", "B001"),
                 "Identifier cannot be empty");
}

TEST_F(RoomTest, EmptyCampusDies) {
    EXPECT_DEATH(Room("Lokaal A", "R001", 30, "", "B001"),
                 "Campus ID cannot be empty");
}

TEST_F(RoomTest, EmptyBuildingDies) {
    EXPECT_DEATH(Room("Lokaal A", "R001", 30, "C001", ""),
                 "Building ID cannot be empty");
}