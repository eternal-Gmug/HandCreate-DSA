#include <iostream>
#include <vector>
#include "QuickSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    Logger::getInstance().log("Starting Quick Sort Application");
    
    // Test Basic Quick Sort
    SortTester::runProb("Quick Sort", quickSort, 100);

    // Test 3-Way
    SortTester::runProb("Quick Sort 3-Way", quickSort3Way, 100);

    // Test Dual Pivot
    SortTester::runProb("Dual Pivot Quick Sort", dualPivotQuickSort, 100);

    system("pause");
    return 0;
}
