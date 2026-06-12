#include "Renovation.h"
#include "DesignByContract.h"

Renovation::Renovation(const std::string& roomId,
                       int start,
                       int end)
        : fRoomId(roomId),
          fStartDay(start),
          fEndDay(end),
          fProperlyInitialized(false) {

    REQUIRE(!roomId.empty(),
            "Room ID voor renovatie mag niet leeg zijn");

    REQUIRE(start > 0,
            "Startdag moet positief zijn");

    REQUIRE(end >= start,
            "Einddag moet na of op de startdag liggen");

    fProperlyInitialized = true;

    ENSURE(isProperlyInitialized(),
           "Renovation niet correct geinitialiseerd");

    ENSURE(fRoomId == roomId,
           "Room ID niet correct opgeslagen");

    ENSURE(fStartDay == start,
           "Startdag niet correct opgeslagen");

    ENSURE(fEndDay == end,
           "Einddag niet correct opgeslagen");
}

bool Renovation::isProperlyInitialized() const {
    bool result = fProperlyInitialized;

    ENSURE(result == true || result == false,
           "Invalid initialization state");

    return result;
}

std::string Renovation::getRoomId() const {
    REQUIRE(isProperlyInitialized(),
            "Renovation niet correct geinitialiseerd");

    std::string result = fRoomId;

    ENSURE(!result.empty(),
           "Room ID mag niet leeg zijn");

    return result;
}

int Renovation::getStartDay() const {
    REQUIRE(isProperlyInitialized(),
            "Renovation niet correct geinitialiseerd");

    int result = fStartDay;

    ENSURE(result > 0,
           "Startdag moet positief zijn");

    return result;
}

int Renovation::getEndDay() const {
    REQUIRE(isProperlyInitialized(),
            "Renovation niet correct geinitialiseerd");

    int result = fEndDay;

    ENSURE(result >= fStartDay,
           "Einddag moet na startdag liggen");

    return result;
}