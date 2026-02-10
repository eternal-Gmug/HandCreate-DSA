#include <iostream>
#include <vector>
#include "RadixSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "Starting Radix Sort Application" << std::endl;
    // Radix sort typically requires non-negative integers.
    // Ensure SortTester produces compatible data (it assumes positive by default).
    SortTester::runProb("Radix Sort", radixSort, 100);
    
    system("pause");
    return 0;
}
