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

    // CRUCIAAL VOOR DE TEST:
    // Gebruik REQUIRE in plaats van een simpele if-check met return.
    // Als LoadFile faalt, MOET het programma stoppen (die).
    REQUIRE(doc.LoadFile(), (std::string("Could not open input file: ") + filename).c_str());

    TiXmlElement* root = doc.FirstChildElement("SYSTEM");
    REQUIRE(root != nullptr, "No <SYSTEM> root tag found.");

    // --- STAP 1: Campussen ---
    for (TiXmlElement* elem = root->FirstChildElement("CAMPUS"); elem != nullptr; elem = elem->NextSiblingElement("CAMPUS")) {
        parseCampus(elem, planner);
    }

    // --- STAP 2: Gebouwen ---
    for (TiXmlElement* elem = root->FirstChildElement("BUILDING"); elem != nullptr; elem = elem->NextSiblingElement("BUILDING")) {
        parseBuilding(elem, planner);
    }

    // --- STAP 3: De rest (Rooms, Meetings, etc.) ---
    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "ROOM") {
            parseRoom(elem, planner);
        } else if (elemName == "MEETING") {
            parseMeeting(elem, planner);
        } else if (elemName == "PARTICIPATION") {
            parseParticipation(elem, planner);
        }
        // Voeg hier eventueel RENOVATION of CATERING toe
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

void SystemParser::parseRoom(TiXmlElement* element, MeetingPlanner& planner) { // Voeg de 'v' van void toe
    TiXmlElement* nameElem = element->FirstChildElement("NAME");
    TiXmlElement* idElem = element->FirstChildElement("IDENTIFIER");
    TiXmlElement* capElem = element->FirstChildElement("CAPACITY");
    TiXmlElement* campusElem = element->FirstChildElement("CAMPUS");
    TiXmlElement* buildElem = element->FirstChildElement("BUILDING");

    if (!nameElem || !idElem || !capElem || !campusElem || !buildElem) {
        std::cerr << "Error: Invalid ROOM information. Skipping.\n";
        return;
    }

    // Veiligere manier om tekst op te halen
    const char* name = nameElem->GetText();
    const char* id = idElem->GetText();
    const char* capText = capElem->GetText();
    const char* campus = campusElem->GetText();
    const char* build = buildElem->GetText();

    if (!name || !id || !capText || !campus || !build) {
        std::cerr << "Error: One of the room fields is empty in XML. Skipping.\n";
        return;
    }

    int capacity = std::stoi(capText);

    Room* roomPtr = new Room(name, id, capacity, campus, build);
    planner.addRoom(roomPtr);
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

    // Kijk of het woordje ONLINE="TRUE" in de XML-tag staat
    const char* onlineAttr = element->Attribute("ONLINE");
    if (onlineAttr != nullptr && std::string(onlineAttr) == "TRUE") {
        meetingPtr->setOnline(true); // Zet de meeting op online
    }

    planner.addMeeting(meetingPtr); // Nu matcht het type: het is een Meeting*
}

void SystemParser::parseParticipation(TiXmlElement* element, MeetingPlanner& planner) {
    // 1. Haal de sub-elementen MEETING en USER op
    TiXmlElement* meetingElem = element->FirstChildElement("MEETING");
    TiXmlElement* userElem = element->FirstChildElement("USER");

    // Veiligheidscheck: bestaan de elementen en zit er tekst in?
    if (!meetingElem || !userElem || !meetingElem->GetText() || !userElem->GetText()) {
        return;
    }

    // --- NIEUW VOOR SYSTEEM 2.0: Check of de user EXTERNAL is ---
    // We kijken in de <USER> tag of er TYPE="EXTERNAL" staat
    bool isExtern = false;
    const char* typeAttr = userElem->Attribute("TYPE");

    if (typeAttr != nullptr && std::string(typeAttr) == "EXTERNAL") {
        isExtern = true;
    }

    // 2. Geef de meetingID, userID én de isExtern-status door aan de planner
    // Let op: zorg dat je addParticipation in MeetingPlanner.h ook 'bool isExternal' accepteert!
    planner.addParticipation(meetingElem->GetText(), userElem->GetText(), isExtern);
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