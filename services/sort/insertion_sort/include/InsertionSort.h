#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 插入排序算法.
    ///
    /// 构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
    ///
    /// @param target 待排序向量.
    void insertionSort(std::vector<int>& target);

    /// @brief 优化后的插入排序 (Binary Insertion Sort).
    ///
    /// 使用二分查找来减少比较操作的次数，但数据移动次数仍然是 O(n^2).
    ///
    /// @param target 待排序向量.
    void insertionSortOptimized(std::vector<int>& target);
}
