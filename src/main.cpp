#include <iostream>
#include "MeetingPlanner.h"
#include "SystemParser.h"
#include "SystemOutput.h"

int main() {
    std::cout << "--- University of Antwerp Meeting Planner ---\n";

    MeetingPlanner planner;
    SystemParser parser;

    // Zorg dat dit pad klopt met waar je XML staat!
    std::string filename = "input/proper_planner.xml";
    std::string reportFile = "report.txt";
    std::string xmlExport = "export_output.xml";

    std::cout << "Attempting to load system...\n";
    parser.loadFile(filename, planner);

    // Check of we echt iets hebben ingeladen
    if (!planner.getRooms().empty()) {
        std::cout << "Success! Data loaded.\n";

        // 1. Voer de simulatie uit (capaciteitscheck)
        planner.processAllMeetings();

        // 2. Genereer het tekst-rapport (voor mensen)
        SystemOutput::generateReport(planner, reportFile);

        // 3. Genereer de XML export (voor Punt 2.2 van je opdracht)
        planner.exportSystem(xmlExport);

        std::cout << "\nAlles is verwerkt. Check " << reportFile << " en " << xmlExport << "\n";
    } else {
        std::cout << "\nFailed to load data. Is de bestandsnaam correct?\n";
    }

    return 0;
}