#ifndef NOPARKING_DATABASE_H
#define NOPARKING_DATABASE_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include "Citation.h"

class Database {
private:
public:
    static const unsigned int SORT_UNSORTED = 0xfbf3a56c;
    static const unsigned int SORT_DATE = 0x28f83216;
    static const unsigned int SORT_PLATES = 0xfac63455;

    unsigned int sortStatus;

    std::vector<std::unique_ptr<Citation>> data;  // The database of parking citations
    /**
     * Creates an interface to a ParkingCitation database.
     */
    Database();

    /**
     * Reads data in from a CSV file. Not exception-safe.
     * @param filename File to read in from
     */
    void readFromCsv(const std::string &filename);

    /**
     * Gets the sort status of the database, as a string.
     * @return Sort status of the database, as a string
     */
    std::string getSortStatusString();

    /**
     * Performs binary search on the database, if possible
     * @param searchQuery The string to search for.
     * @return -2 if unsorted, -1 if not found, index if found.
     */
    int binarySearch(const std::string &searchQuery);
};


#endif //NOPARKING_DATABASE_H
