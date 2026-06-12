#ifndef RENOVATION_H
#define RENOVATION_H

#include <string>

class Renovation {
private:
    std::string fRoomId;
    int fStartDay;
    int fEndDay;
    bool fProperlyInitialized;

public:

    /**
     * REQUIRE(!roomId.empty())
     * REQUIRE(start > 0)
     * REQUIRE(end >= start)
     * ENSURE(isProperlyInitialized())
     * ENSURE(getRoomId() == roomId)
     * ENSURE(getStartDay() == start)
     * ENSURE(getEndDay() == end)
     */
    Renovation(const std::string& roomId, int start, int end);

    /**
     * ENSURE(result == true || result == false)
     */
    bool isProperlyInitialized() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(!result.empty())
     */
    std::string getRoomId() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(result > 0)
     */
    int getStartDay() const;

    /**
     * REQUIRE(isProperlyInitialized())
     * ENSURE(result >= getStartDay())
     */
    int getEndDay() const;
};

#endif