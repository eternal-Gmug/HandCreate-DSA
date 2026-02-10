#include <iostream>
#include <vector>
#include "ShellSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "Starting Shell Sort Application" << std::endl;
    SortTester::runProb("Shell Sort", shellSort, 100);

    system("pause");
    return 0;
}
