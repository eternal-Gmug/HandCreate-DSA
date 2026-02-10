#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 冒泡排序算法实现.
    ///
    /// 基本的冒泡排序，通过重复遍历列表，交换相邻的错误顺序元素。
    /// 时间复杂度 O(n^2).
    ///
    /// @param target 待排序的向量 (原地修改).
    void bubbleSort(std::vector<int>& target);
}
