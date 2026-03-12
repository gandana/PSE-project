#ifndef SYSTEMPARSER_H
#define SYSTEMPARSER_H

#include <string>
#include "MeetingPlanner.h"
#include "tinyxml.h"
#include "DesignByContract.h"

class SystemParser {
private:
    bool properlyInitialized;

    // Helper functions
    void parseRoom(TiXmlElement* element, MeetingPlanner& planner);
    void parseMeeting(TiXmlElement* element, MeetingPlanner& planner);
    void parseParticipation(TiXmlElement* element, MeetingPlanner& planner);

public:
    // Constructor
    SystemParser();

    bool isProperlyInitialized() const { return properlyInitialized; }

    // Main parsing function
    void loadFile(const std::string& filename, MeetingPlanner& planner);
};

#endif // SYSTEMPARSER_H