#include <iostream>
#include <vector>
#include "BucketSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "Starting Bucket Sort Application" << std::endl;
    // Bucket Sort often assumes specific range or positive integers. 
    // Using default random positive integers (0-10000).
    SortTester::runProb("Bucket Sort", bucketSort, 100);
    
    system("pause");
    return 0;
}
