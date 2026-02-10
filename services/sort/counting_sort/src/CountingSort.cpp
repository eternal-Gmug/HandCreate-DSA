#include "CountingSort.h"
#include "Logger.h"

namespace HandCreateDSA {
    void countingSort(std::vector<int>& target){
        // [算法说明]
        // 计数排序的核心是将输入的数据值转化为键存储在额外开辟的数组空间中。
        // 1. 找出待排序的数组中最大和最小的元素
        // 2. 统计数组中每个值为 i 的元素出现的次数，存入数组 C 的第 i 项
        // 3. 对所有的计数累加（从 C 中的第一个元素开始，每一项和前一项相加）
        // 4. 反向填充目标数组：将每个元素 i 放在新数组的第 C(i) 项，每放一个元素就将 C(i) 减去 1
        
        // TODO: 实现具体的计数排序逻辑
        Logger::getInstance().log("CountingSort not implemented yet.");
    }
}
