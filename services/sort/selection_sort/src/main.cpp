#include <iostream>
#include <vector>
#include <chrono>
#include "SelectionSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);

    SortTester::runProb("Selection Sort", selectionSort, 50);
    
    return 0;
}
