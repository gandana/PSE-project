#include <iostream>
#include "MeetingPlanner.h"
#include "SystemParser.h"
#include "SystemOutput.h"

int main() {
    std::cout << "--- University of Antwerp Meeting Planner ---\n";

    MeetingPlanner planner;
    SystemParser parser;

    std::string filename = "input/proper_planner.xml";
    std::string reportFile = "report.txt"; // Save next to our executable

    std::cout << "Attempting to load system from: " << filename << "...\n";
    parser.loadFile(filename, planner);

    if (!planner.getRooms().empty()) {
        std::cout << "\nSuccess! System loaded properly.\n";

        //  Use Case 1.4: Auto-process all meetings
        planner.processAllMeetings();

        //  Use Case 1.2: Generate the Output Report
        SystemOutput::generateReport(planner, reportFile);

    } else {
        std::cout << "\nFailed to load data. Please check the file path.\n";
    }

    return 0;
}