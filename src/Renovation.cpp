#include "Renovation.h"
#include "DesignByContract.h"

Renovation::Renovation(const std::string& roomId, int start, int end) : fRoomId(roomId), fStartDay(start), fEndDay(end) {
    REQUIRE(!roomId.empty(), "Room ID voor renovatie mag niet leeg zijn");
    REQUIRE(start > 0, "Startdag moet positief zijn");
    REQUIRE(end >= start, "Einddag moet na of op de startdag liggen"); // Belangrijk contract!
    
    fProperlyInitialized = true;
    ENSURE(isProperlyInitialized(), "Renovation niet correct geinitialiseerd");
}

bool Renovation::isProperlyInitialized() const { return fProperlyInitialized; }
std::string Renovation::getRoomId() const { return fRoomId; }
int Renovation::getStartDay() const { return fStartDay; }
int Renovation::getEndDay() const { return fEndDay; }