#ifndef SYSTEMPARSER_H
#define SYSTEMPARSER_H

#include <string>
#include "MeetingPlanner.h"
#include "tinyxml.h"

/**
 * @class SystemParser
 * @brief Verantwoordelijk voor het inlezen en parsen van XML invoerbestanden.
 */
class SystemParser {
public:
    /**
     * @brief Constructor voor SystemParser.
     */
    SystemParser();

    /**
     * @brief Controleert of de parser correct is geïnitialiseerd.
     */
    bool isProperlyInitialized() const;

    /**
     * @brief Laadt het systeem in vanuit een XML bestand.
     */
    void loadFile(const std::string& filename, MeetingPlanner& planner);

private:
    bool properlyInitialized;

    // --- NIEUW IN SYSTEEM 2.0 ---
    /**
     * @brief Parst een specifiek <CAMPUS> XML-element.
     */
    void parseCampus(TiXmlElement* element, MeetingPlanner& planner);

    /**
     * @brief Parst een specifiek <BUILDING> XML-element.
     */
    void parseBuilding(TiXmlElement* element, MeetingPlanner& planner);
    // ----------------------------

    /**
     * @brief Parst een specifiek <ROOM> XML-element.
     */
    void parseRoom(TiXmlElement* element, MeetingPlanner& planner);

    /**
     * @brief Parst een specifiek <MEETING> XML-element.
     */
    void parseMeeting(TiXmlElement* element, MeetingPlanner& planner);

    /**
     * @brief Parst participaties binnen een meeting.
     */
    void parseParticipation(TiXmlElement* element, MeetingPlanner& planner);
    void parseRenovation(TiXmlElement* element, MeetingPlanner& planner);
    void parseCatering(TiXmlElement* element, MeetingPlanner& planner);
};

#endif // SYSTEMPARSER_H