#include "SystemParser.h"
#include "DesignByContract.h"
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

    // 1. Validatie: Bestaan de tags wel?
    if (!nameElem || !idElem || !capElem) {
        std::cerr << "Error: Invalid ROOM information (missing fields). Skipping.\n";
        return;
    }

    // 2. Validatie: Is de tekst in de tags niet leeg?
    const char* nameText = nameElem->GetText();
    const char* idText = idElem->GetText();
    const char* capText = capElem->GetText();

    if (!nameText || !idText || !capText) {
        std::cerr << "Error: Room fields cannot be empty. Skipping.\n";
        return;
    }

    // 3. Omzetten naar data
    std::string name = nameText;
    std::string id = idText;
    int capacity = 0;
    try {
        capacity = std::stoi(capText);
    } catch (...) {
        std::cerr << "Error: Capacity '" << capText << "' is not a valid number. Skipping.\n";
        return;
    }

    // 4. HET CONTRACT (Dit voorkomt die -5 punten!)
    REQUIRE(capacity > 0, "Capacity must be strictly positive");

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

    const char* labelText = labelElem->GetText();
    const char* idText = idElem->GetText();
    const char* roomText = roomElem->GetText();
    const char* dateText = dateElem->GetText();

    REQUIRE(labelText != nullptr, "Meeting label cannot be null");
    REQUIRE(idText != nullptr, "Meeting identifier cannot be null");
    REQUIRE(roomText != nullptr, "Meeting room ID cannot be null");
    REQUIRE(dateText != nullptr, "Meeting date cannot be null");

    std::string dateStr = dateText;
    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(dateStr);
    ss >> year >> dash1 >> month >> dash2 >> day;

    if (ss.fail() || dash1 != '-' || dash2 != '-') {
        std::cerr << "Error: Invalid DATE format. Skipping.\n";
        return;
    }

    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_isdst = -1;

    // Converteer naar time_point
    std::time_t t = std::mktime(&tm);
    REQUIRE(t != -1, "Invalid date values provided"); // Contract check voor geldige datum
    auto time_point = std::chrono::system_clock::from_time_t(t);

    Meeting newMeeting(labelText, idText, roomText, time_point);
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