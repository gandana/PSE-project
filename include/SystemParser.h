#ifndef SYSTEMPARSER_H
#define SYSTEMPARSER_H

#include <string>
#include "MeetingPlanner.h"
#include "tinyxml.h"

/**
 * @class SystemParser
 * @brief Verantwoordelijk voor het inlezen en parsen van XML invoerbestanden.
 * * Deze klasse gebruikt de TinyXML bibliotheek om een configuratiebestand in
 * te lezen en om te zetten in Room en Meeting objecten in de MeetingPlanner.
 */
class SystemParser {
public:
    /**
     * @brief Laadt het systeem in vanuit een XML bestand.
     * @param filename Het pad naar het XML bestand.
     * @param planner Een referentie naar de MeetingPlanner waar de data in moet.
     * @post Als het bestand geldig is, bevat de planner de nieuwe kamers en vergaderingen.
     */
    void loadFile(const std::string& filename, MeetingPlanner& planner);

private:
    /**
     * @brief Parst een specifiek <ROOM> XML-element.
     */
    void parseRoom(TiXmlElement* element, MeetingPlanner& planner);

    /**
     * @brief Parst een specifiek <MEETING> XML-element.
     */
    void parseMeeting(TiXmlElement* element, MeetingPlanner& planner);
};

#endif // SYSTEMPARSER_H