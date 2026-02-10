#ifndef SORT_PROFILER_H
#define SORT_PROFILER_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "SortAlgorithm.h"
using namespace std;

// 排序计时 AOP 类
// 在排序前后自动记录数组状态和耗时，并输出到日志文件
class SortProfiler {
    private:
        SortAlgorithm& sorter;
        string logPath;

        // 获取当前时间戳字符串
        string getTimestamp();
        // 将 vector 转为字符串
        string vecToString(const vector<int>& vec);
        // 写入日志
        void writeLog(const string& algorithmName,
                      const vector<int>& before,
                      const vector<int>& after,
                      double elapsedMs);

    public:
        SortProfiler(SortAlgorithm& sorter, const string& logDir = "logs");

        // 通用的 profile 方法：传入排序算法名称和排序函数
        void profile(const string& algorithmName, function<void()> sortFunc, vector<int>& target);

        // 便捷方法：直接按名称调用排序算法并计时
        void selectionSort();
        void selectionSort(vector<int>& target);
        void bubbleSort();
        void bubbleSort(vector<int>& target);
        void insertionSort();
        void insertionSort(vector<int>& target);
        void insertionSort_optimization();
        void insertionSort_optimization(vector<int>& target);
        void shellSort();
        void shellSort(vector<int>& target);
        void mergeSort();
        void mergeSort(vector<int>& target);
        void quickSort();
        void quickSort(vector<int>& target);
        void quickSort3Way();
        void quickSort3Way(vector<int>& target);
        void dualPivotQuickSort();
        void dualPivotQuickSort(vector<int>& target);
        void heapSort();
        void heapSort(vector<int>& target);
        void countingSort();
        void countingSort(vector<int>& target);
        void bucketSort();
        void bucketSort(vector<int>& target);
        void radixSort();
        void radixSort(vector<int>& target);

        // 运行全部排序算法并记录
        void runAll();
        void runAll(vector<int>& target);
};

#endif
