#include <iostream>
#include <vector>
#include <string>
#include "MergeSort.h"
using namespace std;

void MergeSort::merge(vector<std::unique_ptr<Citation>>& plates, int left, int mid, int right) {
    int vector1Length = mid - left + 1;
    int vector2Length = right - mid;

    vector<std::unique_ptr<Citation>> leftVector(vector1Length), rightVector(vector2Length);

    for (int i = 0; i < vector1Length; i++) {
        auto* citation = new Citation(*plates.at(left + i));
        leftVector.at(i) = std::unique_ptr<Citation>(citation);
    }
    for (int i = 0; i < vector2Length; i++) {
        auto* citation = new Citation(*plates.at(mid + 1 + i));
        rightVector.at(i) = std::unique_ptr<Citation>(citation);
    }

    //if (vector1Length != vector2Length)
    //    throw std::logic_error("vector1Length = " + std::to_string(vector1Length) + " but vector2Length = " + std::to_string(vector2Length));

    int leftIndex = 0;
    int rightIndex = 0;
    int mergeIndex = left;

    while (leftIndex < vector1Length || rightIndex < vector2Length) {
        if (leftVector.at(leftIndex)->plateNumber <= rightVector.at(rightIndex)->plateNumber) {
            auto* citation = new Citation(*leftVector.at(leftIndex));
            plates.at(mergeIndex) = std::unique_ptr<Citation>(citation);
            leftIndex++;
        } else {
            auto* citation = new Citation(*leftVector.at(leftIndex));
            plates.at(mergeIndex) = std::unique_ptr<Citation>(citation);
            rightIndex++;
        }
        mergeIndex++;
    }

    while (leftIndex < vector1Length) {
        auto* citation = new Citation(*leftVector.at(leftIndex));
        plates.at(mergeIndex) = std::unique_ptr<Citation>(citation);
        leftIndex++;
        mergeIndex++;
    }

    while (rightIndex < vector2Length) {
        auto* citation = new Citation(*rightVector.at(rightIndex));
        plates.at(mergeIndex) = std::unique_ptr<Citation>(citation);
        rightIndex++;
        mergeIndex++;
    }
}


void MergeSort::mergesort(vector<std::unique_ptr<Citation>>& plates, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergesort(plates, left, mid);
    mergesort(plates, mid + 1, right);
    merge(plates, left, mid, right);
}


void MergeSort::mergeWrapper(std::vector<std::unique_ptr<Citation>> &plates) {
    if (plates.size() <= 1) {
        return;
    }

    std::vector<std::unique_ptr<Citation>> leftVector;
    std::vector<std::unique_ptr<Citation>> rightVector;

    for (int i = 0; i < plates.size() / 2; i++) {
        leftVector.push_back(std::make_unique<Citation>(*plates.at(i)));
    }
    for (int i = (int) plates.size() / 2; i < plates.size(); i++) {
        rightVector.push_back(std::make_unique<Citation>(*plates.at(i)));
    }

    mergeWrapper(leftVector);
    mergeWrapper(rightVector);

    auto leftIterator = leftVector.begin();
    auto rightIterator = rightVector.begin();
    int insertIndex = 0;
    while (leftIterator != leftVector.end() || rightIterator != rightVector.end()) {
        if (leftIterator == leftVector.end()) {
            plates.at(insertIndex) = std::make_unique<Citation>(**rightIterator);
            rightIterator++;
        } else if (rightIterator == rightVector.end()) {
            plates.at(insertIndex) = std::make_unique<Citation>(**leftIterator);
            leftIterator++;
        } else if ((*leftIterator)->plateNumber < (*rightIterator)->plateNumber) {
            plates.at(insertIndex) = std::make_unique<Citation>(**leftIterator);
            leftIterator++;
        } else {
            plates.at(insertIndex) = std::make_unique<Citation>(**rightIterator);
            rightIterator++;
        }
        insertIndex++;
    }
}

void MergeSort::mergeSortDates(vector<std::unique_ptr<Citation>> &citations) {
    if (citations.size() <= 1) {
        return;
    }

    std::vector<std::unique_ptr<Citation>> leftVector;
    std::vector<std::unique_ptr<Citation>> rightVector;

    for (int i = 0; i < citations.size() / 2; i++) {
        leftVector.push_back(std::make_unique<Citation>(*citations.at(i)));
    }
    for (int i = (int) citations.size() / 2; i < citations.size(); i++) {
        rightVector.push_back(std::make_unique<Citation>(*citations.at(i)));
    }

    mergeSortDates(leftVector);
    mergeSortDates(rightVector);

    auto leftIterator = leftVector.begin();
    auto rightIterator = rightVector.begin();
    int insertIndex = 0;
    while (leftIterator != leftVector.end() || rightIterator != rightVector.end()) {
        if (leftIterator == leftVector.end()) {
            citations.at(insertIndex) = std::make_unique<Citation>(**rightIterator);
            rightIterator++;
        } else if (rightIterator == rightVector.end()) {
            citations.at(insertIndex) = std::make_unique<Citation>(**leftIterator);
            leftIterator++;
        } else if ((*leftIterator)->dateTime->getDateTimeString() < (*rightIterator)->dateTime->getDateTimeString()) {
            citations.at(insertIndex) = std::make_unique<Citation>(**leftIterator);
            leftIterator++;
        } else {
            citations.at(insertIndex) = std::make_unique<Citation>(**rightIterator);
            rightIterator++;
        }
        insertIndex++;
    }
};
