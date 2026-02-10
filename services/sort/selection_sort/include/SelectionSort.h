#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 选择排序算法.
    ///
    /// 无论什么数据进去都是 O(n^2) 的时间复杂度。
    /// 所以用到它的时候，数据规模越小越好。
    /// 唯一的好处可能就是不占用额外的内存空间。
    ///
    /// @param target 待排序向量.
    void selectionSort(std::vector<int>& target);
}
