#include <iostream>
#include <windows.h>
#include "SortProfiler.h"
using namespace std;

int main(){
    SetConsoleOutputCP(65001);  // 设置控制台输出为 UTF-8，默认是GBK
    vector<int> arr = {
        38, -5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, -3, 8, 36, 12, 44, 1, 29, 7,
        -12, 93, 55, 81, 64, 17, -8, 73, 42, 60, 22, 35, 91, 11, -15, 68, 3, 87, 14, 53,
        -20, 99, 33, 76, 48, 25, 9, 62, 41, 70, 18, -7, 85, 31, 56, 79, 6, 43, 97, 10,
        -1, 66, 23, 88, 37, 52, 74, 16, 45, 90, 28, 61, 13, -11, 83, 39, 58, 71, 5, 49,
        -18, 95, 30, 77, 40, 21, 63, 84, 0, 57, 34, 72, 20, -9, 86, 32, 54, 78, 67, 98,
        -25, 100, 59, 75, 24, 82, 69, 46, 51, 94, -6, 65, 80, 92, 96, 43, 11, -14, 89, 37
    };
    SortAlgorithm sorter(arr);
    SortProfiler sortProfiler(sorter);
    // 单独计时某个排序
    // sortProfiler.selectionSort();
    // sortProfiler.bubbleSort();
    // sortProfiler.insertionSort();
    // sortProfiler.insertionSort_optimization();
    // sortProfiler.shellSort();
    // sortProfiler.mergeSort();
    // sortProfiler.quickSort();
    // sortProfiler.quickSort3Way();
    // sortProfiler.dualPivotQuickSort();
    // sortProfiler.heapSort();
    // sortProfiler.countingSort();
    // sortProfiler.bucketSort();
    // sortProfiler.radixSort();
    // sortTest.traverse();
    
    sortProfiler.runAll();
    /*防止窗口一闪而过*/
    system("pause");        // 仅限于Windows平台
    // cin.get();           // 读取用户回车的指令，支持跨平台
    return 0;
}
