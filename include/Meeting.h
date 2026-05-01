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
     * @brief Constructor voor een Meeting object.
     */
    Meeting(const std::string& lbl, const std::string& id, const std::string& rId, std::chrono::system_clock::time_point d);

    /**
     * @brief Controleert of het object correct is geïnitialiseerd.
     */
    bool isProperlyInitialized() const;

    // --- GETTERS ---
    const std::string& getLabel() const;
    const std::string& getIdentifier() const;
    const std::string& getRoomId() const;
    std::chrono::system_clock::time_point getDate() const;
    const std::vector<std::string>& getParticipants() const;
    bool isProcessed() const;
    bool isCanceled() const;

    // --- SETTERS & ACTIONS ---
    /**
     * @brief Voegt een deelnemer toe aan de meeting.
     */
    void addParticipant(const std::string& userName);

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