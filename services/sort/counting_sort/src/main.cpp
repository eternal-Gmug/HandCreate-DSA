#include <iostream>
#include <vector>
#include "CountingSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "Starting Counting Sort Application" << std::endl;
    // Counting sort handles repeated values well.
    SortTester::runProb("Counting Sort", countingSort, 100);
    
    system("pause");
    return 0;
}
