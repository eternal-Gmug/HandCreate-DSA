#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 桶排序算法.
    ///
    /// 将数组分到有限数量的桶里。每个桶再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序）。
    /// 适用于元素均匀分布在某个范围内的场景。
    ///
    /// @param target 待排序向量.
    void bucketSort(std::vector<int>& target);
}
