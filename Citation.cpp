#include "Citation.h"

/**
 * Copy resources from another object.
 * @param other Object to copy resources from
 */
void Citation::copyResources(const Citation &other) {
    this->plateNumber = other.plateNumber;
    this->state = other.state;
    this->carMake = other.carMake;
    this->carStyle = other.carStyle;
    this->carColor = other.carColor;
    this->location = other.location;
    this->violation = other.violation;
    this->fine = other.fine;
    this->dateTime = new DateTime(*other.dateTime);
}

Citation::Citation(std::string &plateNumber, std::string &state, std::string &carMake, std::string &carStyle,
                   std::string &carColor, std::string &location, std::string &violation, unsigned int &fine,
                   DateTime &dateTime) {
    this->plateNumber = plateNumber;
    this->state = state;
    this->carMake = carMake;
    this->carStyle = carStyle;
    this->carColor = carColor;
    this->location = location;
    this->violation = violation;
    this->fine = fine;

    // Copy dateTime onto the heap
    this->dateTime = new DateTime(dateTime);
}
Citation::Citation(const Citation &other) {
    // Copy constructor
    copyResources(other);
}
Citation &Citation::operator=(const Citation &other) {
    // Copy assignment operator
    if (this != &other) {
        delete this->dateTime;
        copyResources(other);
    }
    return *this;
}
Citation::~Citation() {
    // Clean up the memory
    delete this->dateTime;
}

Citation::operator std::string() const {
    return this->state + " " + this->plateNumber + " | " + this->carColor + " " + this->carMake + " " + this->carStyle +
    " | Violation: " + this->violation + "\nDate: " + (std::string) *this->dateTime +
    " | Fined $" + std::to_string(this->fine);
}
