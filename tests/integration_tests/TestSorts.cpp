#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "sort.h"
#include "sort_profiler/SortTester.h"

using namespace std;
using namespace HandCreateDSA;

void test_sort(const string& name, void (*sortFunc)(vector<int>&, int), int flag = 1) {
    // 使用新的 SortTester 进行更全面的单元测试
    SortTester::runUnitTests(name, [sortFunc, flag](std::vector<int>& arr){
        sortFunc(arr, flag);
    });
}


int main() {
    test_sort("BubbleSort", Sort::bubbleSort,1);
    test_sort("SelectionSort", Sort::selectionSort);
    test_sort("InsertionSort", Sort::insertionSort);
    test_sort("InsertionSortOptimized", Sort::insertionSortOptimized);
    test_sort("ShellSort", Sort::shellSort);
    test_sort("MergeSort", Sort::mergeSort);
    test_sort("QuickSort", Sort::quickSort);
    test_sort("QuickSort3Way", Sort::quickSort3Way);
    test_sort("DualPivotQuickSort", Sort::dualPivotQuickSort);
    //Add others if implemented
    cout << "All tests passed!" << endl;
    return 0;
}
