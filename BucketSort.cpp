#include "BucketSort.h"

void BucketSort::bucketSort(std::vector<std::unique_ptr<Citation>> &citations, unsigned int recursionDepth) {
    // Using std::unordered_map here so that we can implement the real "internal" sorting algorithm ourselves.
    // It would be more efficient to use std::map, but that would not meet the requirements of the project.
    std::unordered_map<unsigned char, std::vector<std::unique_ptr<Citation>>> buckets;

    // Linked list to store the keys in the correctly sorted order.
    std::list<unsigned char> sortedKeys;
    // Insert '\0' as the first element, as it's guaranteed to be in the unordered_map (see next statement)
    sortedKeys.insert(sortedKeys.begin(), '\0');

    // Special bucket to store strings that have terminated.
    buckets.insert(std::pair('\0', std::vector<std::unique_ptr<Citation>>()));

    // Loop over input vector, sorting into each bucket
    for (std::unique_ptr<Citation>& citationPtr : citations) {
        if (recursionDepth >= citationPtr->plateNumber.size()) {
            // We've reached the end of the string.
            buckets.at('\0').push_back(std::make_unique<Citation>(*citationPtr));
        }
        else {
            unsigned char bucketKey = citationPtr->plateNumber.at(recursionDepth);
            if (buckets.count(bucketKey) == 0) {
                // Create new bucket if the old bucket is not present.
                buckets.insert(std::pair(bucketKey, std::vector<std::unique_ptr<Citation>>()));

                // Perform a pseudo-insertion sort so that we know the correct order of the keys.
                auto currentElementIterator = sortedKeys.begin();
                while (true) {
                    if (bucketKey < *currentElementIterator) {
                        // Insert the key before the current element.
                        sortedKeys.insert(currentElementIterator, bucketKey);
                        break;
                    }
                    if (currentElementIterator == sortedKeys.end()) {
                        // We've reached the end and still haven't found a suitable place to insert.
                        // So the element must belong at the end.
                        sortedKeys.insert(currentElementIterator, bucketKey);
                        break;
                    }
                    // Increment the iterator
                    currentElementIterator++;
                }
            }
            buckets.at(bucketKey).push_back(std::make_unique<Citation>(*citationPtr));
        }
    }

    // "Base case" - terminate if we reach the end of all strings in the bucket
    if (buckets.at('\0').size() == citations.size()) {
        // We've reached the end of all the strings.
        return;
    }

    // Sort all the buckets
    for (auto& bucketPair : buckets) {
        if (bucketPair.first == '\0') continue;  // Skip the "end of string" bucket, as there's nothing to sort there.
        bucketSort(bucketPair.second, recursionDepth + 1);  // Bucket sort the smaller bucket.
    }

    // Concatenate all the buckets. All the buckets in "buckets" map should be sorted now
    unsigned int originalVectorIndex = 0;
    for (const unsigned char& bucketKey : sortedKeys) {
        // Get the keys in order from sortedKeys
        std::vector<std::unique_ptr<Citation>>& currentBucket = buckets.at(bucketKey);
        for (const std::unique_ptr<Citation>& currentCitationPtr : currentBucket) {
            // Copy the new sorted Citations from each bucket to the old vector
            citations.at(originalVectorIndex) = std::make_unique<Citation>(*currentCitationPtr);
            originalVectorIndex++;
        }
        if (originalVectorIndex > citations.size()) {
            throw std::logic_error("Invalid state: originalVectorIndex = " + std::to_string(originalVectorIndex) +
                                   "; citations.size()=" + std::to_string(citations.size()));
        }
    }
}

void BucketSort::bucketSortDate(std::vector<std::unique_ptr<Citation>>& citations, unsigned int recursionDepth) {
// Using std::unordered_map here so that we can implement the real "internal" sorting algorithm ourselves.
    // It would be more efficient to use std::map, but that would not meet the requirements of the project.
    std::unordered_map<unsigned char, std::vector<std::unique_ptr<Citation>>> buckets;

    // Linked list to store the keys in the correctly sorted order.
    std::list<unsigned char> sortedKeys;
    // Insert '\0' as the first element, as it's guaranteed to be in the unordered_map (see next statement)
    sortedKeys.insert(sortedKeys.begin(), '\0');

    // Special bucket to store strings that have terminated.
    buckets.insert(std::pair('\0', std::vector<std::unique_ptr<Citation>>()));

    // Loop over input vector, sorting into each bucket
    for (std::unique_ptr<Citation>& citationPtr : citations) {
        if (recursionDepth >= citationPtr->dateTime->getDateTimeString().size()) {
            // We've reached the end of the string.
            buckets.at('\0').push_back(std::make_unique<Citation>(*citationPtr));
        }
        else {
            unsigned char bucketKey = citationPtr->dateTime->getDateTimeString().at(recursionDepth);
            if (buckets.count(bucketKey) == 0) {
                // Create new bucket if the old bucket is not present.
                buckets.insert(std::pair(bucketKey, std::vector<std::unique_ptr<Citation>>()));

                // Perform a pseudo-insertion sort so that we know the correct order of the keys.
                auto currentElementIterator = sortedKeys.begin();
                while (true) {
                    if (bucketKey < *currentElementIterator) {
                        // Insert the key before the current element.
                        sortedKeys.insert(currentElementIterator, bucketKey);
                        break;
                    }
                    if (currentElementIterator == sortedKeys.end()) {
                        // We've reached the end and still haven't found a suitable place to insert.
                        // So the element must belong at the end.
                        sortedKeys.insert(currentElementIterator, bucketKey);
                        break;
                    }
                    // Increment the iterator
                    currentElementIterator++;
                }
            }
            buckets.at(bucketKey).push_back(std::make_unique<Citation>(*citationPtr));
        }
    }

    // "Base case" - terminate if we reach the end of all strings in the bucket
    if (buckets.at('\0').size() == citations.size()) {
        // We've reached the end of all the strings.
        return;
    }

    // Sort all the buckets
    for (auto& bucketPair : buckets) {
        if (bucketPair.first == '\0') continue;  // Skip the "end of string" bucket, as there's nothing to sort there.
        bucketSortDate(bucketPair.second, recursionDepth + 1);  // Bucket sort the smaller bucket.
    }

    // Concatenate all the buckets. All the buckets in "buckets" map should be sorted now
    unsigned int originalVectorIndex = 0;
    for (const unsigned char& bucketKey : sortedKeys) {
        // Get the keys in order from sortedKeys
        std::vector<std::unique_ptr<Citation>>& currentBucket = buckets.at(bucketKey);
        for (const std::unique_ptr<Citation>& currentCitationPtr : currentBucket) {
            // Copy the new sorted Citations from each bucket to the old vector
            citations.at(originalVectorIndex) = std::make_unique<Citation>(*currentCitationPtr);
            originalVectorIndex++;
        }
        if (originalVectorIndex > citations.size()) {
            throw std::logic_error("Invalid state: originalVectorIndex = " + std::to_string(originalVectorIndex) +
                                   "; citations.size()=" + std::to_string(citations.size()));
        }
    }
}

void BucketSort::bucketSortWrapper(std::vector<std::unique_ptr<Citation>> &citations) {
    bucketSort(citations, 0);
}

void BucketSort::bucketSortDateWrapper(std::vector<std::unique_ptr<Citation>>& citations) {
    bucketSortDate(citations, 0);
}
