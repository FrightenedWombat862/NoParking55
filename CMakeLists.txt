cmake_minimum_required(VERSION 3.24)
project(NoParking)

set(CMAKE_CXX_STANDARD 17)

add_executable(NoParking main.cpp MergeSort.cpp MergeSort.h BucketSort.cpp BucketSort.h Database.cpp Database.h Citation.cpp Citation.h DateTime.cpp DateTime.h PatienceSort.cpp PatienceSort.h PatienceSortDate.h PatienceSortDate.cpp)
