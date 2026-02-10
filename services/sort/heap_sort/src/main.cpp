#include <iostream>
#include <vector>
#include "HeapSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "Starting Heap Sort Application" << std::endl;
    SortTester::runProb("Heap Sort", heapSort, 100);
    
    system("pause");
    return 0;
}
