#include "Database.h"

Database::Database() {

}

void Database::readFromCsv(const std::string &filename) {
    if (!std::filesystem::exists(filename)) {
        throw std::ios_base::failure("In Database::readFromCsv(), file \"" + filename + "\" not found.");
    }

    std::ifstream inputFileStream(filename, std::ios_base::in);

    // Read file line-by-line
    for (std::string line; getline(inputFileStream, line);) {

        if (line.find("Data.") != std::string::npos && line.find("Date.") != std::string::npos) {
            // Skip this iteration if this is the header row.
            continue;
        }

        // Expected format: 
        // NumberPlate,State,Make,Style,Color,Location,Violation,Fine,Year,Month,Day,Hour,Minute
        std::vector<std::string> inputLineVector;

        // Populate the vector with the values
        while (!line.empty()) {
            // Extract everything up to the comma
            inputLineVector.push_back(line.substr(0, line.find(',')));
            line.erase(0, line.find(','));  // Erase everything up to and including the comma
            if (!line.empty() && line.at(0) == ',') {
                line.erase(0, 1);  // Erase the comma as well if present.
            }
        }

        // Remove quotation marks if present.
        for (auto &inputLineVectorElement : inputLineVector) {
            if (inputLineVectorElement.back() == '\"') {
                inputLineVectorElement.pop_back();
            }
            if (inputLineVectorElement.front() == '\"') {
                // Erase the front character
                inputLineVectorElement.erase(0, 1);
            }
        }

        // Error handling, to avoid surprises.
        if (inputLineVector.size() != 13) {
            throw std::logic_error("In Database::readFromCsv(), expected 13 elements in inputLineVector(), got " +
                std::to_string(inputLineVector.size()));
        }

        // Initialize fine and dateTime.
        unsigned int fine = std::stoi(inputLineVector.at(7));
        DateTime dateTime((unsigned int) std::stoi(inputLineVector.at(8)),
                          (unsigned short) std::stoi(inputLineVector.at(9)),
                          (unsigned short) std::stoi(inputLineVector.at(10)),
                          (unsigned short) std::stoi(inputLineVector.at(11)),
                          (unsigned short) std::stoi(inputLineVector.at(12)));

        // Add unique ptr to vector
        this->data.push_back(std::make_unique<Citation>(inputLineVector.at(0), inputLineVector.at(1),
                                                         inputLineVector.at(2), inputLineVector.at(3),
                                                         inputLineVector.at(4), inputLineVector.at(5),
                                                         inputLineVector.at(6), fine, dateTime));
    }
}
