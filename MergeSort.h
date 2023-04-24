#ifndef NOPARKING_MERGESORT_H
#define NOPARKING_MERGESORT_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Citation.h"

class MergeSort {
private:
    static void merge(std::vector<std::unique_ptr<Citation>> &plates, int left, int mid, int right);
public:
	static void mergesort(std::vector<std::unique_ptr<Citation>> &plates, int left, int right);
    static void mergeWrapper(std::vector<std::unique_ptr<Citation>> &plates);
    static void mergeSortDates(std::vector<std::unique_ptr<Citation>> &citations);
};

#endif //NOPARKING_MERGESORT_H
