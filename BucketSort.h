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
public:
    static void bucketSort(std::vector<std::unique_ptr<Citation>> &citations, unsigned int recursionDepth);
    static void bucketSortWrapper(std::vector<std::unique_ptr<Citation>>& citations);
};


#endif //NOPARKING_BUCKETSORT_H
