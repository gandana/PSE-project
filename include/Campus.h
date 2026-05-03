#ifndef CAMPUS_H
#define CAMPUS_H

#include <string>
#include "DesignByContract.h"

class Campus {
private:
    std::string fName;
    std::string fIdentifier;
    bool fProperlyInitialized;

public:
    Campus(const std::string& name, const std::string& id);
    bool isProperlyInitialized() const;
    const std::string& getName() const;
    const std::string& getIdentifier() const;
};

#endif