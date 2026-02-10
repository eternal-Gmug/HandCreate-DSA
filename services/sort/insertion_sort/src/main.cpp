#include <iostream>
#include <vector>
#include "InsertionSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "Starting Insertion Sort Application" << std::endl;
    
    // Test Standard Insertion Sort
    SortTester::runProb("Insertion Sort", insertionSort, 50);

    // Test Optimized Insertion Sort
    SortTester::runProb("Insertion Sort Optimized", insertionSortOptimized, 50);
    
    system("pause");
    return 0;
}
