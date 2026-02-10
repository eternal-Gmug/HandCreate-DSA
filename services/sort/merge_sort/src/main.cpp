#include <iostream>
#include <vector>
#include "MergeSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "Starting Merge Sort Application" << std::endl;
    SortTester::runProb("Merge Sort", mergeSort, 100);

    system("pause");
    return 0;
}
