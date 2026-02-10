#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "sort_profiler/SortTester.h"

using namespace std;
using namespace HandCreateDSA;

void test_sort(const string& name, void (*sortFunc)(vector<int>&)) {
    // 使用新的 SortTester 进行更全面的单元测试
    SortTester::runUnitTests(name, [sortFunc](std::vector<int>& arr){
        sortFunc(arr);
    });
}


int main() {
    test_sort("BubbleSort", bubbleSort);
    test_sort("SelectionSort", selectionSort);
    test_sort("InsertionSort", insertionSort);
    test_sort("InsertionSortOptimized", insertionSortOptimized);
    test_sort("ShellSort", shellSort);
    test_sort("MergeSort", mergeSort);
    test_sort("QuickSort", quickSort);
    test_sort("QuickSort3Way", quickSort3Way);
    test_sort("DualPivotQuickSort", dualPivotQuickSort);
    // Add others if implemented
    cout << "All tests passed!" << endl;
    return 0;
}
