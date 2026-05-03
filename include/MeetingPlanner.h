#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

#include <vector>
#include "Campus.h"
#include "Building.h"
#include "Room.h"
#include "Meeting.h"
#include "Renovation.h"
#include "Catering.h"

class MeetingPlanner {
private:
    std::vector<Campus*> fCampuses;
    std::vector<Building*> fBuildings;
    std::vector<Room*> fRooms;      // Gebruik pointers voor consistentie met Systeem 2.0
    std::vector<Meeting*> fMeetings;
    std::vector<Renovation*> fRenovations;
    std::vector<Catering*> fCaterings;

    void exportSystem(const std::string& filename) const;
    
    bool fProperlyInitialized;

public:
    MeetingPlanner();
    ~MeetingPlanner(); // Cruciaal voor geheugenbeheer van de pointers!

    bool isProperlyInitialized() const;

    // Functies voor de parser
    void addCampus(Campus* c);
    void addBuilding(Building* b);
    void addRoom(Room* r);
    void addMeeting(Meeting* m);
    void addRenovation(Renovation* ren);
    void addCatering(Catering* cat);
    // In MeetingPlanner.h
    void addParticipation(const std::string& meetingId, const std::string& userId);

    // Hulpmiddelen voor consistentie (Appendix B)
    bool campusExists(const std::string& id) const;
    bool buildingExists(const std::string& id) const;
};

#endif