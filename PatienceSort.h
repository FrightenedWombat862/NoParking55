#ifndef NOPARKING_PATIENCESORT_H
#define NOPARKING_PATIENCESORT_H

#include <list>
#include <memory>
#include <queue>
#include <vector>
#include "Citation.h"

class PatienceSort {
protected:
    static void heapifyDown(std::vector<std::list<std::unique_ptr<Citation>>> &cardStacks, std::size_t elementToHeapify);
public:
    static void patienceSort(std::vector<std::unique_ptr<Citation>>& citations);
};


#endif //NOPARKING_PATIENCESORT_H
