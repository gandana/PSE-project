#include "SystemParser.h"
#include "DesignByContract.h"
#include "Campus.h"
#include "Building.h"
#include "Room.h"
#include "Meeting.h"
#include "MeetingPlanner.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>

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

    // --- STAP 1: Eerst alle CAMPUS elementen inlezen ---
    for (TiXmlElement* elem = root->FirstChildElement("CAMPUS"); elem != nullptr; elem = elem->NextSiblingElement("CAMPUS")) {
        parseCampus(elem, planner);
    }

    // --- STAP 2: Dan alle BUILDING elementen ---
    for (TiXmlElement* elem = root->FirstChildElement("BUILDING"); elem != nullptr; elem = elem->NextSiblingElement("BUILDING")) {
        parseBuilding(elem, planner);
    }

    // --- STAP 3: De rest van de elementen in de juiste volgorde ---
    // We lopen nog een keer door de root om de rest te vinden
    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "ROOM") {
            parseRoom(elem, planner);
        } else if (elemName == "MEETING") {
            parseMeeting(elem, planner);
        } else if (elemName == "PARTICIPATION") {
            parseParticipation(elem, planner);
        }
    }
}

void SystemParser::parseCampus(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* nameElem = element->FirstChildElement("NAME");
    TiXmlElement* idElem = element->FirstChildElement("IDENTIFIER");

    if (!nameElem || !idElem || !nameElem->GetText() || !idElem->GetText()) {
        std::cerr << "Error: Invalid CAMPUS information (missing fields).\n";
        return;
    }

    Campus* newCampus = new Campus(nameElem->GetText(), idElem->GetText());
    planner.addCampus(newCampus);
}

void SystemParser::parseBuilding(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* nameElem = element->FirstChildElement("NAME");
    TiXmlElement* idElem = element->FirstChildElement("IDENTIFIER");
    TiXmlElement* campusElem = element->FirstChildElement("CAMPUS");

    if (!nameElem || !idElem || !campusElem || !nameElem->GetText() || !idElem->GetText() || !campusElem->GetText()) {
        std::cerr << "Error: Invalid BUILDING information (missing fields).\n";
        return;
    }

    Building* newBuilding = new Building(nameElem->GetText(), idElem->GetText(), campusElem->GetText());
    planner.addBuilding(newBuilding);
}

void SystemParser::parseRoom(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* nameElem = element->FirstChildElement("NAME");
    TiXmlElement* idElem = element->FirstChildElement("IDENTIFIER");
    TiXmlElement* capElem = element->FirstChildElement("CAPACITY");
    TiXmlElement* campusElem = element->FirstChildElement("CAMPUS");
    TiXmlElement* buildElem = element->FirstChildElement("BUILDING");

    if (!nameElem || !idElem || !capElem || !campusElem || !buildElem) {
        std::cerr << "Error: Invalid ROOM information. Skipping.\n";
        return;
    }

    int capacity = std::stoi(capElem->GetText());

    // FIX: Gebruik 'new' om een pointer te maken
    Room* roomPtr = new Room(nameElem->GetText(), idElem->GetText(), capacity,
                             campusElem->GetText(), buildElem->GetText());

    planner.addRoom(roomPtr); // Nu matcht het type: het is een Room*
}

void SystemParser::parseMeeting(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* labelElem = element->FirstChildElement("LABEL");
    TiXmlElement* idElem = element->FirstChildElement("IDENTIFIER");
    TiXmlElement* roomElem = element->FirstChildElement("ROOM");
    TiXmlElement* dateElem = element->FirstChildElement("DATE");

    if (!labelElem || !idElem || !roomElem || !dateElem || !labelElem->GetText() || !idElem->GetText() || !roomElem->GetText() || !dateElem->GetText()) {
        std::cerr << "Error: Invalid MEETING information.\n";
        return;
    }

    // (Datum conversie logica blijft hetzelfde...)
    std::string dateStr = dateElem->GetText();
    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(dateStr);
    ss >> year >> dash1 >> month >> dash2 >> day;

    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_isdst = -1;
    std::time_t t = std::mktime(&tm);
    auto time_point = std::chrono::system_clock::from_time_t(t);

    // FIX: Gebruik 'new' om een pointer te maken
    Meeting* meetingPtr = new Meeting(labelElem->GetText(), idElem->GetText(),
                                      roomElem->GetText(), time_point);

    planner.addMeeting(meetingPtr); // Nu matcht het type: het is een Meeting*
}

void SystemParser::parseParticipation(TiXmlElement* element, MeetingPlanner& planner) {
    TiXmlElement* meetingElem = element->FirstChildElement("MEETING");
    TiXmlElement* userElem = element->FirstChildElement("USER");

    if (!meetingElem || !userElem || !meetingElem->GetText() || !userElem->GetText()) {
        return;
    }

    planner.addParticipation(meetingElem->GetText(), userElem->GetText());
}
void SystemParser::parseRenovation(TiXmlElement* element, MeetingPlanner& planner) {
    const char* room = element->FirstChildElement("ROOM") ? element->FirstChildElement("ROOM")->GetText() : nullptr;
    TiXmlElement* startElem = element->FirstChildElement("START");
    TiXmlElement* endElem = element->FirstChildElement("END");

    if (room && startElem && endElem) {
        int start = std::stoi(startElem->GetText());
        int end = std::stoi(endElem->GetText());
        planner.addRenovation(new Renovation(room, start, end));
    }
}

void SystemParser::parseCatering(TiXmlElement* element, MeetingPlanner& planner) {
    const char* provider = element->FirstChildElement("PROVIDER") ? element->FirstChildElement("PROVIDER")->GetText() : nullptr;
    const char* building = element->FirstChildElement("BUILDING") ? element->FirstChildElement("BUILDING")->GetText() : nullptr;

    if (provider && building) {
        planner.addCatering(new Catering(provider, building));
    }
}