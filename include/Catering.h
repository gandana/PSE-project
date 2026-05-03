#ifndef CATERING_H
#define CATERING_H

#include <string>

class Catering {
private:
    std::string fProviderName;
    std::string fBuildingId;
    bool fProperlyInitialized;

public:
    Catering(const std::string& provider, const std::string& buildingId);
    bool isProperlyInitialized() const;

    std::string getProviderName() const;
    std::string getBuildingId() const;
};

#endif