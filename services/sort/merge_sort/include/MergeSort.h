#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 归并排序算法.
    ///
    /// 采用分治法（Divide and Conquer）的一个非常典型的应用。
    /// 将已有序的子序列合并，得到完全有序的序列。
    /// 时间复杂度始终为 O(n log n)，但需要额外的 O(n) 内存空间。
    ///
    /// @param target 待排序向量.
    void mergeSort(std::vector<int>& target);
}
