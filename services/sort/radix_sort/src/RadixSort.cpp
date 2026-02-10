#include "RadixSort.h"
#include "Logger.h"

namespace HandCreateDSA {
    void radixSort(std::vector<int>& target){
        // [算法说明]
        // 基数排序是非比较型整数排序算法。
        // 原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。
        // 具体实现：
        // 1. 取得数组中的最大数，并取得位数
        // 2. arr 为原始数组，从最低位开始取每个位组成 radix 数组
        // 3. 对 radix 进行计数排序（利用计数排序适用于小范围数的特点）
        
        // TODO: 实现具体的基数排序逻辑
        Logger::getInstance().log("RadixSort not implemented yet.");
    }
}
