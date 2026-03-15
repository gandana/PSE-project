#ifndef SYSTEMOUTPUT_H
#define SYSTEMOUTPUT_H

#include "MeetingPlanner.h"
#include <string>

class SystemOutput {
public:
    // Use Case 1.2
    static void generateReport(const MeetingPlanner& planner, const std::string& filename);
};

#endif // SYSTEMOUTPUT_H