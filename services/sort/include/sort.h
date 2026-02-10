#pragma once
#include <vector>

namespace HandCreateDSA {
    class Sort {
    public:
        /// @brief 冒泡排序算法实现.
        ///
        /// 基本的冒泡排序，通过重复遍历列表，交换相邻的错误顺序元素。
        /// 时间复杂度 O(n^2).
        ///
        /// @param target 待排序的向量 (原地修改).
        static void bubbleSort(std::vector<int>& target);

        /// @brief 标准快速排序算法.
        ///
        /// 使用单基准（Pivot）的快速排序实现。
        /// 分治策略：选择一个基准，将数组分为小于和大于基准的两部分，递归排序。
        ///
        /// @param target 待排序的向量.
        static void quickSort(std::vector<int>& target);

        /// @brief 三路快速排序算法 (3-Way Quick Sort).
        ///
        /// 适用于存在大量重复元素的数组。
        /// 核心思想：将数组分为 < pivot, = pivot, > pivot 三部分，仅递归 < 和 > 的部分。
        ///
        /// @param target 待排序的向量.
        static void quickSort3Way(std::vector<int>& target);

        /// @brief 双基准快速排序算法 (Dual-Pivot Quick Sort).
        ///
        /// 使用两个基准点 (p1, p2) 将数组分为三段进行递归排序 (<p1, p1~p2, >p2)。
        /// 通常比单基准版本有更少的交换次数和更高的效率。
        ///
        /// @param target 待排序的向量.
        static void dualPivotQuickSort(std::vector<int>& target);

        /// @brief 归并排序算法.
        ///
        /// 采用分治法（Divide and Conquer）的一个非常典型的应用。
        /// 将已有序的子序列合并，得到完全有序的序列。
        /// 时间复杂度始终为 O(n log n)，但需要额外的 O(n) 内存空间。
        ///
        /// @param target 待排序向量.
        static void mergeSort(std::vector<int>& target);

        /// @brief 插入排序算法.
        ///
        /// 构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
        ///
        /// @param target 待排序向量.
        static void insertionSort(std::vector<int>& target);

        /// @brief 优化后的插入排序 (Binary Insertion Sort).
        ///
        /// 使用二分查找来减少比较操作的次数，但数据移动次数仍然是 O(n^2).
        ///
        /// @param target 待排序向量.
        static void insertionSortOptimized(std::vector<int>& target);

        /// @brief 选择排序算法.
        ///
        /// 无论什么数据进去都是 O(n^2) 的时间复杂度。
        /// 所以用到它的时候，数据规模越小越好。
        /// 唯一的好处可能就是不占用额外的内存空间。
        ///
        /// @param target 待排序向量.
        static void selectionSort(std::vector<int>& target);

        /// @brief 堆排序算法.
        ///
        /// 利用堆（Heap）这种数据结构所设计的一种排序算法。
        /// 堆是一个近似完全二叉树的结构，并同时满足堆积的性质：即子节点的键值或索引总是小于（或者大于）它的父节点。
        /// 时间复杂度 O(n log n)，不稳定排序。
        ///
        /// @param target 待排序向量.
        static void heapSort(std::vector<int>& target);

        /// @brief 计数排序算法.
        ///
        /// 一种非比较的排序算法，适用于整数排序。
        /// 核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。
        /// 要求输入的数据必须是有确定范围的整数。
        /// 时间复杂度为 O(n+k)，其中 k 是整数的范围。
        ///
        /// @param target 待排序向量.
        static void countingSort(std::vector<int>& target);

        /// @brief 桶排序算法.
        ///
        /// 将数组分到有限数量的桶里。每个桶再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序）。
        /// 适用于元素均匀分布在某个范围内的场景。
        ///
        /// @param target 待排序向量.
        static void bucketSort(std::vector<int>& target);

        /// @brief 基数排序算法.
        ///
        /// 按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。
        /// 有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序。
        /// 最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。
        ///
        /// @param target 待排序向量.
        static void radixSort(std::vector<int>& target);

        /// @brief 希尔排序算法.
        ///
        /// 是插入排序的一种更高效的改进版本，也称为缩小增量排序。
        /// 希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；
        /// 随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。
        ///
        /// @param target 待排序向量.
        static void shellSort(std::vector<int>& target);
    };
}
