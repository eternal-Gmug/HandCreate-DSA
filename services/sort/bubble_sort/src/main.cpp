#include <iostream>
#include <vector>
#include <chrono>
#include "BubbleSort.h"
#include "sort_profiler/SortTester.h"
#include <windows.h>

using namespace HandCreateDSA;

int main() {
    SetConsoleOutputCP(65001);

    // 使用 SortTester 生成测试数据并运行测试
    // 这里使用较小的数据规模，方便观察
    SortTester::runProb("Bubble Sort", bubbleSort, 50);
    
    return 0;
}
