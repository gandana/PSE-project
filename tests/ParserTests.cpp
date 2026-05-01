#include <gtest/gtest.h>
#include "../include/SystemParser.h"
#include "../include/MeetingPlanner.h"

class ParserTest : public ::testing::Test {
protected:
    MeetingPlanner planner;
    SystemParser parser;
};

// Test 1: Proving it successfully loads a good file
TEST_F(ParserTest, LoadValidSystem) {
    std::string filename = "input/proper_planner.xml";
    parser.loadFile(filename, planner);

    // It should load exactly 2 rooms and 2 meetings
    EXPECT_FALSE(planner.getRooms().empty());
    EXPECT_EQ(planner.getRooms().size(), 2);
    EXPECT_EQ(planner.getMeetings().size(), 2);
}

// Test 2: Proving it handles an invalid file properly
TEST_F(ParserTest, LoadInvalidSystem) {
    std::string filename = "input/invalid_planner.xml";

    // Omdat we nu REQUIRE(capacity > 0) hebben, MOET het programma crashen.
    // ASSERT_DEATH controleert of dat gebeurt.
    ASSERT_DEATH({
        parser.loadFile(filename, planner);
    }, "Capacity must be strictly positive");
}

// Test 3: Proving it survives if a file completely doesn't exist
TEST_F(ParserTest, FileNotFound) {
    std::string filename = "input/this_file_does_not_exist.xml";

    // Hier hebben we geen REQUIRE voor (alleen een cerr),
    // dus deze test mag wel gewoon draaien zonder te crashen.
    // We maken even een lokale planner zodat we zeker weten dat die leeg is.
    MeetingPlanner freshPlanner;
    parser.loadFile(filename, freshPlanner);

    EXPECT_TRUE(freshPlanner.getRooms().empty());
}