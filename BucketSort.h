#ifndef NOPARKING_BUCKETSORT_H
#define NOPARKING_BUCKETSORT_H

#include <list>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "Citation.h"

class BucketSort {
private:
    static void bucketSort(std::vector<std::unique_ptr<Citation>> &citations, unsigned int recursionDepth);
    static void bucketSortDate(std::vector<std::unique_ptr<Citation>> &citations, unsigned int recursionDepth);
public:
    /**
     * Bucket sort vector of Citations by plate number
     * @param citations
     */
    static void bucketSortWrapper(std::vector<std::unique_ptr<Citation>>& citations);
    /**
     * Bucket sort vector of Citations by date
     * @param citations
     */
    static void bucketSortDateWrapper(std::vector<std::unique_ptr<Citation>>& citations);
};


#endif //NOPARKING_BUCKETSORT_H
