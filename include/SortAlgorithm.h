#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SortAlgorithm {
    private:
        static inline vector<int> emptyVec;    // 内部的静态空向量
        vector<int>& pending;
    public:
        bool hasParamter = false;
        SortAlgorithm():pending(emptyVec){}
        SortAlgorithm(vector<int>& target):pending(target),hasParamter(true){}
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
        void traverse();
        void traverse(vector<int>& target);
        vector<int>& getPending();
        void test();
};
