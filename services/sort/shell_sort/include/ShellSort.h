#pragma once
#include <vector>

namespace HandCreateDSA {
    /// @brief 希尔排序算法.
    ///
    /// 是插入排序的一种更高效的改进版本，也称为缩小增量排序。
    /// 希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；
    /// 随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。
    ///
    /// @param target 待排序向量.
    void shellSort(std::vector<int>& target);
}
