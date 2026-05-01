#include "SystemOutput.h"
#include <fstream>
#include <iomanip>
#include <iostream>

void SystemOutput::generateReport(const MeetingPlanner& planner, const std::string& filename) {
    std::ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file: " << filename << "\n";
        return;
    }

    outFile << "--- System Report ---\n\n";

    // Print all meetings
    outFile << "Meetings:\n";
    for (const auto& meeting : planner.getMeetings()) {
        // Convert time_point to time_t for printing
        std::time_t t = std::chrono::system_clock::to_time_t(meeting.getDate());
        std::tm* tm_ptr = std::localtime(&t);

        outFile << meeting.getRoomId() << ", " << std::put_time(tm_ptr, "%d/%m/%Y") << "\n";
        outFile << meeting.getLabel() << "\n";
        
        // Print participants separated by commas
        const auto& participants = meeting.getParticipants();
        for (size_t i = 0; i < participants.size(); ++i) {
            outFile << participants[i];
            if (i < participants.size() - 1) outFile << ", ";
        }
        
        outFile << "\nMeeting ID: " << meeting.getIdentifier() << "\n";
        
        // Indicate if it was canceled due to conflict
        if (meeting.isCanceled()) {
            outFile << "Status: CANCELED (Room Conflict)\n";
        } else if (meeting.isProcessed()) {
            outFile << "Status: PROCESSED\n";
        }
        outFile << "\n";
    }

    // Print all rooms
    outFile << "Rooms:\n";
    for (const auto& room : planner.getRooms()) {
        outFile << room.getName() << "\n";
        outFile << "Capacity: " << room.getCapacity() << " people\n";
        outFile << "Room ID: " << room.getIdentifier() << "\n\n";
    }

    outFile.close();
    std::cout << "Report successfully generated at: " << filename << "\n";
}