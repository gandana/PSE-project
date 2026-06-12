#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

#include <vector>
#include <string> // Cruciaal voor std::string!
#include "DesignByContract.h" // Zorg dat dit bestand in je include map staat
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
    std::vector<Room*> fRooms;
    std::vector<Meeting*> fMeetings;
    std::vector<Renovation*> fRenovations;
    std::vector<Catering*> fCaterings;

    bool fProperlyInitialized;

public:
    /**
     * ENSURE(isProperlyInitialized())
     */
    MeetingPlanner();    ~MeetingPlanner();

    bool isProperlyInitialized() const;

    // Functies voor de parser
    /**
     * REQUIRE(isProperlyInitialized())
     * REQUIRE(c != nullptr)
     * ENSURE(campusExists(c->getIdentifier()))
     */
    void addCampus(Campus* c);

    /**
     * REQUIRE(isProperlyInitialized())
     * REQUIRE(b != nullptr)
     * ENSURE(buildingExists(b->getIdentifier()))
     */
    void addBuilding(Building* b);

    /**
     * REQUIRE(isProperlyInitialized())
     * REQUIRE(r != nullptr)
     * ENSURE(room is added)
     */
    void addRoom(Room* r);

    /**
     * REQUIRE(isProperlyInitialized())
     * REQUIRE(m != nullptr)
     * ENSURE(meeting is added)
     */
    void addMeeting(Meeting* m);
    void addRenovation(Renovation* ren);
    void addCatering(Catering* cat);

    /**
     * REQUIRE(isProperlyInitialized())
     * REQUIRE(!meetingId.empty())
     * REQUIRE(!userId.empty())
     * ENSURE(participant is added to the correct meeting)
     */
    void addParticipation(const std::string& meetingId,
                          const std::string& userId,
                          bool isExternal = false);

    /**
     * REQUIRE(isProperlyInitialized())
     * REQUIRE(!filename.empty())
     * ENSURE(output file is created)
     */
    void exportSystem(const std::string& filename) const;
    void runSimulation();

    const std::vector<Room*>& getRooms() const { return fRooms; }
    const std::vector<Meeting*>& getMeetings() const { return fMeetings; }

    void processAllMeetings();

    // Hulpmiddelen voor consistentie
    bool campusExists(const std::string& id) const;
    bool buildingExists(const std::string& id) const;
};

#endif