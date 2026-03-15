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
    parser.loadFile(filename, planner);

    // It should print an error and skip the bad room, leaving rooms empty.
    EXPECT_TRUE(planner.getRooms().empty());
}

// Test 3: Proving it survives if a file completely doesn't exist
TEST_F(ParserTest, FileNotFound) {
    std::string filename = "input/this_file_does_not_exist.xml";
    parser.loadFile(filename, planner);

    // Should handle the missing file cleanly without crashing
    EXPECT_TRUE(planner.getRooms().empty());
}