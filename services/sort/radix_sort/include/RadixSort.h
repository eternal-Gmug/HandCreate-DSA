#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 基数排序算法.
    ///
    /// 按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。
    /// 有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序。
    /// 最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。
    ///
    /// @param target 待排序向量.
    void radixSort(std::vector<int>& target);
}
