#ifndef SYSTEMOUTPUT_H
#define SYSTEMOUTPUT_H

#include "MeetingPlanner.h"
#include <string>

/**
 * @class SystemOutput
 * @brief Zorgt voor het genereren van output rapporten.
 * * Scheidt de output-logica (het schrijven naar tekstbestanden) van de
 * kernlogica (de MeetingPlanner), wat zorgt voor een sterker object-georiënteerd design.
 */
class SystemOutput {
public:
    /**
     * @brief Genereert een tekstueel rapport van alle kamers en vergaderingen.
     * @param planner De planner waarvan de data gelezen moet worden.
     * @param filename De naam van het bestand waar het rapport in wordt opgeslagen (bijv. "report.txt").
     * @post Een tekstbestand is aangemaakt op de harde schijf.
     */
    static void generateReport(const MeetingPlanner& planner, const std::string& filename);
};

#endif // SYSTEMOUTPUT_H