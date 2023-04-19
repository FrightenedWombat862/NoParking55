#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Database.h"
#include "MergeSort.h"
#include "BucketSort.h"
using namespace std;

/*
The Plan:
 - Merge sort the license plate numbers
 - Radix sort or bucket sort the date/time.
 */

int main() {

    const string SORT_UNSORTED = "unsorted";
    const string SORT_DATE = "date/time";
    const string SORT_PLATES = "license plates";

    string sortStatus = SORT_UNSORTED;

    Database database;
    database.readFromCsv("parking_citations.csv");

    // NOTE: The parsed data is in vector form at database.data.
    // Access it by doing *(database.data.at(index))
    // If passing into a function, remember to pass by REFERENCE. Otherwise the code will be *very* slow.

    //cout << "Removing all but the first 10000 elements..." << endl;
    //database.data.erase(database.data.begin() + 8, database.data.end());

    cout << "Welcome to No Parking (version 1.0)" << endl;
    cout << "Type \"help\" for help" << endl;
    while (true) {
        string inputLine;
        cout << endl << "Sorted by: " << sortStatus << " >";  // Terminal prompt
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
        if (command.at(0) == 'f') {
            // TODO Implement binary search
            cout << "Find command not implemented yet..." << endl;
        }
        if (command.at(0) == 'g') {
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
            cout << "License plate number: " << endl;
            cout << database.data.at(indexToGet)->plateNumber << endl;
            cout << std::string(*(database.data.at(indexToGet)->dateTime)) << endl;
            cout << database.data.at(indexToGet)->state << " | " << database.data.at(indexToGet)->carColor <<
                " " << database.data.at(indexToGet)->carMake << " " << database.data.at(indexToGet)->carStyle <<
                " | Fined $" << database.data.at(indexToGet)->fine << endl;
        }
        else if (command.at(0) == 'q') {
            // quit
            break;
        }
        else if (command.at(0) == 's') {
            // sort
            if (firstArgument.empty()) {
                cout << "Command \"sort\" requires one argument <algorithm>, which can be either m for merge or b for bucket." << endl;
            }
            else if (firstArgument.at(0) == 'm') {
                cout << "Now merge sorting license plates..." << endl;
                MergeSort::mergeWrapper(database.data);
                cout << "Information about the first citation:" << endl;
                cout << database.data.at(0)->plateNumber << endl;
                cout << std::string(*(database.data.at(0)->dateTime)) << endl;
                sortStatus = SORT_PLATES;
            }
            else if (firstArgument.at(0) == 'b') {
                cout << "Now bucket sorting license plates..." << endl;
                BucketSort::bucketSortWrapper(database.data);
                cout << "Information about the first citation:" << endl;
                cout << database.data.at(0)->plateNumber << endl;
                cout << std::string(*(database.data.at(0)->dateTime)) << endl;
                sortStatus = SORT_PLATES;
            }
            else {
                cout << "Please type m for merge sort or b for bucket sort." << endl;
            }
        }
        else {
            // Help
            cout << "Commands list:" << endl;
            cout << "find <query> - Searches for a parking citation number." << endl;
            cout << "get <index> - Gets the parking citation at a specific index" << endl;
            cout << "help - Displays this help message" << endl;
            cout << "quit - Exits the program" << endl;
            cout << "sort <algorithm> <field> - Sorts citations. Algorithm is m for merge sort or\n" <<
                "b for bucket sort. Field can be p for license plates or d for dates." << endl;
        }
    }
}
