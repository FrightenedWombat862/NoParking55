#ifndef NOPARKING_CITATION_H
#define NOPARKING_CITATION_H

#include "DateTime.h"

class Citation {
protected:
    void copyResources(const Citation &other);
public:
    std::string plateNumber;
    std::string state;
    std::string carMake;
    std::string carStyle;
    std::string carColor;
    std::string location;
    std::string violation;
    unsigned int fine;
    DateTime* dateTime;

    // Constructor and other useful memory management.
    Citation(std::string &plateNumber, std::string &state, std::string &carMake, std::string &carStyle, std::string &carColor,
             std::string &location, std::string &violation, unsigned int &fine, DateTime &dateTime);
    Citation(const Citation &other);
    Citation& operator=(const Citation& other);
    ~Citation();

    explicit operator std::string() const;  // Allow conversion into a string
};


#endif //NOPARKING_CITATION_H
