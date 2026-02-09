#include <iostream>
#include <windows.h>
#include "SortProfiler.h"
using namespace std;

int main(){
    SetConsoleOutputCP(65001);  // 设置控制台输出为 UTF-8，默认是GBK
    vector<int> arr = {38, -5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, -3, 8, 36, 12, 44, 1, 29, 7};
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
    sortProfiler.dualPivotQuickSort();
    // sortTest.traverse();
    
    /*防止窗口一闪而过*/
    system("pause");        // 仅限于Windows平台
    // cin.get();           // 读取用户回车的指令，支持跨平台
    return 0;
}
