#include "SystemOutput.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>

void SystemOutput::generateReport(const MeetingPlanner& planner, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file: " << filename << "\n";
        return;
    }

    outFile << "## ==== [SYSTEM STATUS] ==== ##\n\n";

    // --- 1. MEETINGS PRINTEN ---
    outFile << "Meetings:\n";
    // Let op: we gebruiken Meeting* omdat het pointers zijn
    for (Meeting* meeting : planner.getMeetings()) {

        // Tijd omzetten naar leesbaar formaat
        std::time_t t = std::chrono::system_clock::to_time_t(meeting->getDate());
        std::tm* tm_ptr = std::localtime(&t);

        // Gebruik overal -> in plaats van .
        outFile << meeting->getRoomId() << ", " << std::put_time(tm_ptr, "%d/%m/%Y") << "\n";
        outFile << meeting->getLabel() << "\n";

        // Deelnemers printen
        const auto& participants = meeting->getParticipants();
        for (size_t i = 0; i < participants.size(); ++i) {
            outFile << participants[i];
            if (i < participants.size() - 1) outFile << ", ";
        }

        outFile << "\nMeeting ID: " << meeting->getIdentifier() << "\n";

        // Status printen (Canceled of Processed)
        if (meeting->isCanceled()) {
            outFile << "Status: CANCELED (Capaciteitsprobleem of Conflict)\n";
        } else if (meeting->isProcessed()) {
            outFile << "Status: PROCESSED\n";
        }
        outFile << "\n";
    }

    outFile << "--------------------------\n";

    // --- 2. KAMERS PRINTEN ---
    outFile << "Rooms:\n";
    // Let op: we gebruiken Room*
    for (Room* room : planner.getRooms()) {
        outFile << room->getName() << "\n";
        outFile << "Capacity: " << room->getCapacity() << " people\n";
        outFile << "Room ID: " << room->getIdentifier() << "\n\n";
    }

    outFile.close();
    std::cout << "Report successfully generated at: " << filename << "\n";
}