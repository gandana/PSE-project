#ifndef INC_MEETING_H
#define INC_MEETING_H

#include <string>
#include <chrono>
#include <vector>
#include "DesignByContract.h"

/**
 * @class Meeting
 * @brief Representatie van een vergadering in het systeem.
 */
class Meeting {
private:
    bool fIsOnline;
    bool fAllowsExternals;
    // We houden bij hoeveel externen er zijn voor de CO2 berekening
    int fExternalCount;
    std::string fLabel;
    std::string fIdentifier;
    std::string fRoomId;
    std::chrono::system_clock::time_point fDate;
    std::vector<std::string> fParticipants;
    bool fProperlyInitialized;
    bool fProcessed;
    bool fCanceled;

public:
    /**
     * @brief Geeft de datum terug als een leesbare string (YYYY-MM-DD).
     */
    std::string getDateString() const;
    /**
     * @brief Constructor voor een Meeting object.
     */
    Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d);

    /**
     * @brief Controleert of het object correct is geïnitialiseerd.
     */
    bool isProperlyInitialized() const;
    /**
     * @brief Geeft het aantal deelnemers aan de meeting terug.
     * @return Het aantal deelnemers als integer.
     */
    int getParticipantCount() const;

    // --- GETTERS ---
    const std::string& getLabel() const;
    const std::string& getIdentifier() const;
    const std::string& getRoomId() const;
    std::chrono::system_clock::time_point getDate() const;
    const std::vector<std::string>& getParticipants() const;
    bool isProcessed() const;
    bool isCanceled() const;
    bool isOnline() const;
    void setOnline(bool online);
    double calculateCO2() const; // De nieuwe rekenfunctie


    // --- SETTERS & ACTIONS ---
    /**
     * @brief Voegt een deelnemer toe aan de meeting.
     */
    void addParticipant(const std::string& userName, bool isExternal = false);

    /**
     * @brief Zet de verwerkingsstatus van de meeting.
     */
    void setProcessed(bool status);

    /**
     * @brief Zet de geannuleerde status van de meeting.
     */
    void setCanceled(bool status);

};

#endif // INC_MEETING_H