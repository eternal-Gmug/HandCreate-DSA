#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 计数排序算法.
    ///
    /// 一种非比较的排序算法，适用于整数排序。
    /// 核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。
    /// 要求输入的数据必须是有确定范围的整数。
    /// 时间复杂度为 O(n+k)，其中 k 是整数的范围。
    ///
    /// @param target 待排序向量.
    void countingSort(std::vector<int>& target);
}
