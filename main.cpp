#include <chrono>
#include <iostream>
#include <string>
#include "Database.h"
#include "MergeSort.h"
#include "BucketSort.h"
#include "PatienceSort.h"
using namespace std;

/*
The Plan:
 - Merge sort the license plate numbers
 - Radix sort or bucket sort the date/time.
 */

int main() {
    const string fileLocation = "parking_citations.csv";

    Database database;
    database.readFromCsv(fileLocation);

    // NOTE: The parsed data is in vector form at database.data.
    // Access it by doing *(database.data.at(index))
    // If passing into a function, remember to pass by REFERENCE. Otherwise the code will be *very* slow.

    //cout << "Removing all but the first 10000 elements..." << endl;
    //database.data.erase(database.data.begin() + 8, database.data.end());

    cout << "Welcome to No Parking (version 1.0)" << endl;
    cout << "Type \"help\" for help" << endl;
    while (true) {
        string inputLine;
        cout << endl << "Sorted by: " << database.getSortStatusString() << " >";  // Terminal prompt
        getline(cin, inputLine);

        // If there is one argument, lastArgument is the one that will be populated
        // If there are two arguments, both middleArgument and lastArgument are populated
        string command;
        string firstArgument;
        string secondArgument;

        if (inputLine.find(' ') == string::npos) {
            // No arguments.
            command = inputLine.substr(0, inputLine.find(' '));
        }
        else if (inputLine.find_first_of(' ') == inputLine.find_last_of(' ')) {
            // 1 argument.
            command = inputLine.substr(0, inputLine.find(' '));
            firstArgument = inputLine.substr(inputLine.find(' '));
            firstArgument.erase(firstArgument.find(' '), 1);
        }
        else {
            // 2 arguments
            command = inputLine.substr(0, inputLine.find(' '));
            firstArgument = inputLine.substr(inputLine.find(' '), inputLine.find_last_of(' ') - inputLine.find(' '));
            firstArgument.erase(firstArgument.find(' '), 1);
            secondArgument = inputLine.substr(inputLine.find_last_of(' '));
            secondArgument.erase(secondArgument.find(' '), 1);
        }
        if (command.empty()) {
            cout << "Please enter a command. Type \"help\" for help" << endl;
        }
        else if (command.at(0) == 'f') {
            // find
            if (firstArgument.empty()) {
                cout << "Command \"find\" requires one argument <query>." << endl;
            }
            else {
                auto startTime = chrono::system_clock::now();  // Get start time
                int index = database.binarySearch(firstArgument);
                auto endTime = chrono::system_clock::now();  // Get end time
                std::chrono::duration<double> elapsedTime = endTime - startTime;
                if (index == -2) {
                    cout << "Cannot run command \"find\" before sorting input" << endl;
                }
                else if (index == -1) {
                    cout << "No results for query \"" << firstArgument << "\"" << endl;
                }
                else {
                    cout << "Found results at index " << std::to_string(index) << endl;
                    // Print ALL elements that match the query.
                    if (database.sortStatus == Database::SORT_PLATES) {
                        int currentlyPrinting = index;
                        while (currentlyPrinting >= 0 && database.data.at(currentlyPrinting)->plateNumber == firstArgument) {
                            cout << (std::string) *database.data.at(currentlyPrinting) << endl;
                            currentlyPrinting--;
                        }
                        currentlyPrinting = index + 1;
                        while (currentlyPrinting < database.data.size() && database.data.at(currentlyPrinting)->plateNumber == firstArgument) {
                            cout << (std::string) *database.data.at(currentlyPrinting) << endl;
                            currentlyPrinting++;
                        }
                    }
                    else if (database.sortStatus == Database::SORT_DATE) {
                        int currentlyPrinting = index;
                        while (currentlyPrinting >= 0 && database.data.at(currentlyPrinting)->dateTime->getDateTimeString() == firstArgument) {
                            cout << (std::string) *database.data.at(currentlyPrinting) << endl;
                            currentlyPrinting--;
                        }
                        currentlyPrinting = index + 1;
                        while (currentlyPrinting < database.data.size() && database.data.at(currentlyPrinting)->dateTime->getDateTimeString() == firstArgument) {
                            cout << (std::string) *database.data.at(currentlyPrinting) << endl;
                            currentlyPrinting++;
                        }
                    }
                }
                if (index != -2) {
                    cout << "The binary search took " << elapsedTime.count() << " seconds." << endl;
                }
            }
        }
        else if (command.at(0) == 'g') {
            // get
            int indexToGet = 0;  // The index to get
            try {
                // Parse the argument as an integer
                indexToGet = std::stoi(firstArgument);
                if (indexToGet < 0) {
                    cout << "Expected <index> in get command to be positive, got " << firstArgument << endl;
                    continue;
                }
            }
            catch (std::invalid_argument &e) {
                cout << "get command requires an integer as the first argument, not \"" << firstArgument << '\"' << endl;
                continue;
            }
            cout << (string) *database.data.at(indexToGet) << endl;
        }
        else if (command.at(0) == 'l') {
            // linear search
            if (firstArgument.empty()) {
                cout << "Command \"lfind\" requires one argument <query>." << endl;
            }
            else {
                auto startTime = chrono::system_clock::now();  // Get start time
                int index = database.linearSearchLicensePlate(firstArgument);
                auto endTime = chrono::system_clock::now();  // Get end time
                std::chrono::duration<double> elapsedTime = endTime - startTime;
                if (index != -1) {
                    cout << (std::string) *database.data.at(index) << endl;
                }
                else {
                    cout << "License plate \"" << firstArgument << "\" not found" << endl;
                }
                cout << "The linear search took " << elapsedTime.count() << " seconds." << endl;
            }
        }
        else if (command.at(0) == 'q') {
            // quit
            break;
        }
        else if (command.at(0) == 'r') {
            // reload
            database.data.clear();  // Empty the database.
            database.readFromCsv(fileLocation);  // Reread data from CSV
            database.sortStatus = Database::SORT_UNSORTED;  // Mark as unsorted
            cout << "Successfully reloaded data from disk" << endl;
        }
        else if (command.at(0) == 's') {
            // sort
            if (firstArgument.empty()) {
                cout << "Command \"sort\" requires one argument <algorithm>, which can be m for merge, b for bucket, or p for patience." << endl;
            }
            else if (firstArgument.at(0) == 'm') {
                cout << "Now merge sorting license plates..." << endl;
                auto startTime = chrono::system_clock::now();  // Get start time
                MergeSort::mergeWrapper(database.data);
                auto endTime = chrono::system_clock::now();  // Get end time
                std::chrono::duration<double> elapsedTime = endTime - startTime;
                cout << "Took " << elapsedTime.count() << " seconds to sort." <<  endl;
                database.sortStatus = Database::SORT_PLATES;
            }
            else if (firstArgument.at(0) == 'b') {
                cout << "Now bucket sorting license plates..." << endl;
                auto startTime = chrono::system_clock::now();  // Get start time
                BucketSort::bucketSortWrapper(database.data);
                auto endTime = chrono::system_clock::now();  // Get end time
                std::chrono::duration<double> elapsedTime = endTime - startTime;
                cout << "Took " << elapsedTime.count() << " seconds to sort." <<  endl;
                database.sortStatus = Database::SORT_PLATES;
            }
            else if (firstArgument.at(0) == 'p') {
                cout << "Now patience sorting license plates..." << endl;
                auto startTime = chrono::system_clock::now();  // Get start time
                PatienceSort::patienceSort(database.data);
                auto endTime = chrono::system_clock::now();  // Get end time
                std::chrono::duration<double> elapsedTime = endTime - startTime;
                cout << "Took " << elapsedTime.count() << " seconds to sort." <<  endl;
                database.sortStatus = Database::SORT_PLATES;
            }
            else {
                cout << "Please type m for merge sort or b for bucket sort." << endl;
            }
        }
        else {
            // help
            cout << "Commands list:" << endl;
            cout << "find <query> - Performs binary search for a parking citation" << endl;
            cout << "get <index> - Gets the parking citation at a specific index" << endl;
            cout << "help - Displays this help message" << endl;
            cout << "lfind <query> - Performs linear search for a license plate number" << endl;
            cout << "reload - Reloads the database from file" << endl;
            cout << "quit - Exits the program" << endl;
            cout << "sort <algorithm> <field> - Sorts citations. Algorithm is m for merge sort, \n" <<
                "b for bucket sort, or p for patience sort. Field can be l for license plates or d for dates." << endl;
        }
    }
}
