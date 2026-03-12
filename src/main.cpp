#include <iostream>
#include "MeetingPlanner.h"
#include "SystemParser.h"

int main() {
    std::cout << "--- University of Antwerp Meeting Planner ---" << std::endl;

    MeetingPlanner planner;
    SystemParser parser;

    // Making sure valid_planner.xml is inside an "input" folder in the project root!
    std::string filename = "input/valid_planner.xml";

    std::cout << "Attempting to load system from: " << filename << "...\n";

    // This will parse the file and run the consistency checks
    parser.loadFile(filename, planner);

    // If loadFile succeeds and the system is consistent, it reaches here
    std::cout << "\nSuccess! System loaded properly." << std::endl;
    std::cout << "Total Rooms loaded: " << planner.getRooms().size() << std::endl;
    std::cout << "Total Meetings loaded: " << planner.getMeetings().size() << std::endl;

    return 0;
}