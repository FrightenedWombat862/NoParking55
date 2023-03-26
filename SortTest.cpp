#include "SortTest.h"

void SortTest::selectionSort(std::vector<std::unique_ptr<Citation>> &citations) {
    // sortIndex is the index which we are currently interested in finding the correct element for
    for (unsigned int sortIndex = 0; sortIndex < citations.size(); sortIndex++) {
        unsigned int minIndex = sortIndex;  // Index with the minimum element
        for (unsigned int checkIndex = sortIndex + 1; checkIndex < citations.size(); checkIndex++) {
            if (*(citations.at(sortIndex)->dateTime) < *(citations.at(minIndex)->dateTime)) {
                minIndex = sortIndex;  // New minimum
            }
        }
        std::swap(citations.at(sortIndex), citations.at(minIndex));  // Swap the pointers
    }
}