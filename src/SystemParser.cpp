#include "SystemParser.h"
#include <iostream>
#include <sstream>
#include <ctime>

SystemParser::SystemParser() : properlyInitialized(true) {
    ENSURE(isProperlyInitialized(), "SystemParser not initialized");
}
bool SystemParser::isProperlyInitialized() const {
    return properlyInitialized;
}

void SystemParser::loadFile(const std::string& filename, MeetingPlanner& planner) {
    REQUIRE(isProperlyInitialized(), "SystemParser not properly initialized");
    REQUIRE(!filename.empty(), "Filename cannot be empty");

    TiXmlDocument doc(filename.c_str());
    if (!doc.LoadFile()) {
        std::cerr << "Error: Could not open input file: " << filename << "\n";
        return;
    }

    TiXmlElement* root = doc.FirstChildElement("SYSTEM");
    if (!root) {
        std::cerr << "Error: No <SYSTEM> root tag found.\n";
        return;
    }

    // Loop through all elements
    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "ROOM") {
            parseRoom(elem, planner);
        } else if (elemName == "MEETING") {
            parseMeeting(elem, planner);
        } else if (elemName == "PARTICIPATION") {
            parseParticipation(elem, planner);
        } else {
            std::cerr << "Warning: Unknown element <" << elemName << "> found. Skipping.\n";
        }
    }


}

void SystemParser::parseRoom(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* nameElem = element->FirstChildElement("NAME");
    TiXmlElement* idElem = element->FirstChildElement("IDENTIFIER");
    TiXmlElement* capElem = element->FirstChildElement("CAPACITY");

    if (!nameElem || !idElem || !capElem) {
        std::cerr << "Error: Invalid ROOM information (missing fields). Skipping.\n";
        return; // [Invalid info]: Print error and continue
    }

    std::string name = nameElem->GetText() ? nameElem->GetText() : "";
    std::string id = idElem->GetText() ? idElem->GetText() : "";
    int capacity = std::stoi(capElem->GetText());

    if (capacity <= 0) {
        std::cerr << "Error: CAPACITY must be strictly greater than 0. Skipping room.\n";
        return;
    }

    Room newRoom(name, id, capacity);
    planner.addRoom(newRoom);
}

void SystemParser::parseMeeting(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* labelElem = element->FirstChildElement("LABEL");
    TiXmlElement* idElem = element->FirstChildElement("IDENTIFIER");
    TiXmlElement* roomElem = element->FirstChildElement("ROOM");
    TiXmlElement* dateElem = element->FirstChildElement("DATE");

    if (!labelElem || !idElem || !roomElem || !dateElem) {
        std::cerr << "Error: Invalid MEETING information (missing fields). Skipping.\n";
        return;
    }

    std::string label = labelElem->GetText() ? labelElem->GetText() : "";
    std::string id = idElem->GetText() ? idElem->GetText() : "";
    std::string roomId = roomElem->GetText() ? roomElem->GetText() : "";
    std::string dateStr = dateElem->GetText() ? dateElem->GetText() : "";

    if (label.empty() || id.empty() || roomId.empty()) {
        std::cerr << "Error: NAME, LABEL, and IDENTIFIER cannot be empty. Skipping meeting.\n";
        return;
    }

    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(dateStr);

    // Extract the integers and the dashes
    ss >> year >> dash1 >> month >> dash2 >> day;

    if (ss.fail() || dash1 != '-' || dash2 != '-') {
        std::cerr << "Error: Invalid DATE format for meeting " << id << ". Expected YYYY-MM-DD. Skipping.\n";
        return;
    }

    // Manually map to the std::tm structure
    std::tm tm = {};
    tm.tm_year = year - 1900; // std::tm counts years since 1900
    tm.tm_mon = month - 1;    // std::tm counts months from 0 to 11
    tm.tm_mday = day;
    tm.tm_isdst = -1;         // Let the system determine daylight savings

    auto time_point = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    // Create and add the meeting
    Meeting newMeeting(label, id, roomId, time_point);
    planner.addMeeting(newMeeting);
}

void SystemParser::parseParticipation(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* meetingElem = element->FirstChildElement("MEETING");
    TiXmlElement* userElem = element->FirstChildElement("USER");

    if (!meetingElem || !userElem) {
        std::cerr << "Error: Invalid PARTICIPATION information (missing fields). Skipping.\n";
        return;
    }

    std::string meetingId = meetingElem->GetText() ? meetingElem->GetText() : "";
    std::string userName = userElem->GetText() ? userElem->GetText() : "";

    if (userName.empty() || meetingId.empty()) {
        std::cerr << "Error: USER and MEETING cannot be empty in participation. Skipping.\n";
        return;
    }

    // Attempt to link the user to the meeting
    planner.addParticipation(meetingId, userName);
}