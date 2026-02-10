#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 标准快速排序算法.
    ///
    /// 使用单基准（Pivot）的快速排序实现。
    /// 分治策略：选择一个基准，将数组分为小于和大于基准的两部分，递归排序。
    ///
    /// @param target 待排序的向量.
    void quickSort(std::vector<int>& target);

    /// @brief 三路快速排序算法 (3-Way Quick Sort).
    ///
    /// 适用于存在大量重复元素的数组。
    /// 核心思想：将数组分为 < pivot, = pivot, > pivot 三部分，仅递归 < 和 > 的部分。
    ///
    /// @param target 待排序的向量.
    void quickSort3Way(std::vector<int>& target);

    /// @brief 双基准快速排序算法 (Dual-Pivot Quick Sort).
    ///
    /// 使用两个基准点 (p1, p2) 将数组分为三段进行递归排序 (<p1, p1~p2, >p2)。
    /// 通常比单基准版本有更少的交换次数和更高的效率。
    ///
    /// @param target 待排序的向量.
    void dualPivotQuickSort(std::vector<int>& target);
}
