#include <gtest/gtest.h>
#include "Room.h"

// Test valid room creation
TEST(RoomTest, DefaultConstructor) {
    Room room("M.G.025", "Room_1", 55);
    EXPECT_EQ(room.getName(), "M.G.025");
    EXPECT_EQ(room.getCapacity(), 55);
}

// Test that an empty name triggers a contract violation (requirement)
TEST(RoomTest, InvalidCapacity) {
    // In a real scenario, gtest can catch the assertion failure from DesignByContract
    EXPECT_DEATH(Room("ErrorRoom", "ID1", 0), ""); 
}