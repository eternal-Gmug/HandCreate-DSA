#include "ShellSort.h"
#include <algorithm>
#include "Logger.h"

namespace HandCreateDSA {
    void shellSort(std::vector<int>& target){
        // Logger::getInstance().log("ShellSort started.");
        int n = target.size();
        
        // [增量序列]
        // 初始增量 gap = n/2，每轮循环 gap 减半，直到 gap = 0
        // 这种增量序列（Shell序列）的时间复杂度最坏情况仍为 O(n^2)
        // 更好的序列有 Hibbard 或 Sedgewick 序列
        for (int gap = n / 2; gap > 0; gap /= 2) {
            
            // [分组插入排序]
            // 从第 gap 个元素开始，对每个元素进行"跨步"插入排序
            // 这里的 i 代表当前待插入元素的位置
            for (int i = gap; i < n; i++) {
                
                int temp = target[i];
                int j;
                
                // [寻找插入位置]
                // 在当前分组内（索引间隔为 gap），向前寻找 temp 的正确位置
                // j >= gap 保证 j-gap 索引有效
                for (j = i; j >= gap && target[j - gap] > temp; j -= gap) {
                    target[j] = target[j - gap];
                }
                
                // [插入]
                target[j] = temp;
            }
        }
        // Logger::getInstance().log("ShellSort finished.");
    }
}
