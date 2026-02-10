#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 堆排序算法.
    ///
    /// 利用堆（Heap）这种数据结构所设计的一种排序算法。
    /// 堆是一个近似完全二叉树的结构，并同时满足堆积的性质：即子节点的键值或索引总是小于（或者大于）它的父节点。
    /// 时间复杂度 O(n log n)，不稳定排序。
    ///
    /// @param target 待排序向量.
    void heapSort(std::vector<int>& target);
}
