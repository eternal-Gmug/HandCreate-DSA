#include "BubbleSort.h"
#include "Logger.h"
#include <algorithm>

namespace HandCreateDSA {
    void bubbleSort(std::vector<int>& target){
        Logger::getInstance().log("BubbleSort started.");
        
        // [外层循环]
        // 控制遍历的轮数。每完成一轮，最大的元素就会"冒泡"到最后。
        int n = target.size();
        for(int j=n-1; j>0; j--){
            // [内层循环]
            // 相邻元素两两比较，如果顺序错误则交换。
            // j 是当前未排序部分的边界。
            for(int i=0; i<j; i++){
                if(target[i] > target[i+1]){
                    std::swap(target[i], target[i+1]);
                }
            }
        }
        Logger::getInstance().log("BubbleSort finished.");
    }
}
