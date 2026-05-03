#ifndef RENOVATION_H
#define RENOVATION_H

#include <string>

class Renovation {
private:
    std::string fRoomId;
    int fStartDay; // Bijv. dag van het jaar (1-365)
    int fEndDay;
    bool fProperlyInitialized;

public:
    Renovation(const std::string& roomId, int start, int end);
    bool isProperlyInitialized() const;
    
    // Getters
    std::string getRoomId() const;
    int getStartDay() const;
    int getEndDay() const;
};

#endif