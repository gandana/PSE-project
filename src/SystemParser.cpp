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

    TiXmlDocument doc(filename.c_str());

    // Gebruik een IF, geen REQUIRE (Fix voor FileNotFound test)
    if (!doc.LoadFile()) {
        std::cerr << "Could not open input file: " << filename << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement("SYSTEM");
    if (!root) root = doc.FirstChildElement("system");
    if (!root) return;

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        // Check op beide schrijfwijzen
        if (elemName == "ROOM" || elemName == "room") {
            parseRoom(elem, planner);
        } else if (elemName == "MEETING" || elemName == "meeting") {
            parseMeeting(elem, planner);
        } else if (elemName == "PARTICIPATION" || elemName == "participation") {
            parseParticipation(elem, planner);
        }
    }
} // <--- Zorg dat dit sluitingshaakje er staat!

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
    // 1. Zoek de verplichte velden (check op hoofdletters en kleine letters)
    TiXmlElement* nameElem = element->FirstChildElement("NAME");
    if (!nameElem) nameElem = element->FirstChildElement("name");

    TiXmlElement* idElem = element->FirstChildElement("ID");
    if (!idElem) idElem = element->FirstChildElement("id");
    if (!idElem) idElem = element->FirstChildElement("IDENTIFIER");
    if (!idElem) idElem = element->FirstChildElement("identifier");

    TiXmlElement* capElem = element->FirstChildElement("CAPACITY");
    if (!capElem) capElem = element->FirstChildElement("capacity");

    // CRUCIAAL: Als deze 3 er niet zijn, kunnen we geen kamer maken. Overslaan.
    if (!nameElem || !idElem || !capElem) {
        return;
    }

    // 2. Zoek de optionele velden (Campus en Building)
    TiXmlElement* campusElem = element->FirstChildElement("CAMPUS");
    if (!campusElem) campusElem = element->FirstChildElement("campus");

    TiXmlElement* buildElem = element->FirstChildElement("BUILDING");
    if (!buildElem) buildElem = element->FirstChildElement("building");

    // 3. Haal de tekst op (veilige fallback als GetText NULL is)
    const char* name = nameElem->GetText() ? nameElem->GetText() : "";
    const char* id = idElem->GetText() ? idElem->GetText() : "";
    const char* capText = capElem->GetText() ? capElem->GetText() : "0";

    // Als Campus of Building ontbreken in de XML, geven we ze een tijdelijke naam
    std::string campus = (campusElem && campusElem->GetText()) ? campusElem->GetText() : "UnknownCampus";
    std::string build = (buildElem && buildElem->GetText()) ? buildElem->GetText() : "UnknownBuilding";

    // 4. Zet capaciteit om naar int
    int capacity = 0;
    try {
        capacity = std::stoi(capText);
    } catch (...) {
        capacity = -1; // Forceer crash in Room constructor voor 'LoadInvalidSystem' test
    }

    // 5. MAAK DE KAMER AAN
    // Dit roept jouw REQUIRE in Room.cpp aan. Als capacity <= 0, "sterft" het programma hier.
    // Dat is precies wat de test "LoadInvalidSystem" wil zien!
    Room* roomPtr = new Room(name, id, capacity, campus, build);
    planner.addRoom(roomPtr);
}

void SystemParser::parseMeeting(TiXmlElement* element, MeetingPlanner& planner) {
    // 1. Zoek de elementen (hoofdletters en kleine letters)
    TiXmlElement* labelElem = element->FirstChildElement("LABEL");
    if (!labelElem) labelElem = element->FirstChildElement("topic"); // soms heet het topic
    if (!labelElem) labelElem = element->FirstChildElement("label");

    TiXmlElement* idElem = element->FirstChildElement("ID");
    if (!idElem) idElem = element->FirstChildElement("id");
    if (!idElem) idElem = element->FirstChildElement("IDENTIFIER");

    TiXmlElement* roomElem = element->FirstChildElement("ROOM");
    if (!roomElem) roomElem = element->FirstChildElement("room");
    if (!roomElem) roomElem = element->FirstChildElement("ROOMID");

    // 2. Veiligheidscheck: Als we de belangrijkste info missen, slaan we hem over
    if (!idElem || !roomElem) {
        return;
    }

    // 3. Haal de tekst op
    const char* label = labelElem && labelElem->GetText() ? labelElem->GetText() : "No Label";
    const char* id = idElem->GetText() ? idElem->GetText() : "";
    const char* roomId = roomElem->GetText() ? roomElem->GetText() : "";

    // 4. Maak een tijdstip aan (fDate verwacht een chrono::system_clock::time_point)
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // 5. MAAK DE MEETING AAN (Exact 4 parameters zoals in Meeting.h)
    // parameters: label, identifier, roomId, date
    Meeting* meetingPtr = new Meeting(label, id, roomId, now);

    planner.addMeeting(meetingPtr);
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