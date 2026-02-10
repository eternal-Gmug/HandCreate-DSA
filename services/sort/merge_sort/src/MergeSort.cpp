#include "MergeSort.h"
#include <vector>

namespace HandCreateDSA {
    // [合并函数] Merge
    // 将两个有序子区间 [left, mid] 和 [mid+1, right] 合并为一个有序区间
    static void merge(std::vector<int>& target, int left, int right, int mid){
        int n = right - left + 1;
        std::vector<int> sortedArray(n,0); // 临时数组，O(n) 空间消耗
        int i = left;      // 左区间指针
        int j = mid + 1;   // 右区间指针
        int count = 0;     // 临时数组索引
        
        while(count < n){
            if(i > mid){
                // 左区间已取完，取右区间其余部分
                sortedArray[count++] = target[j++];
            }
            else if(j > right){
                // 右区间已取完，取左区间其余部分
                sortedArray[count++] = target[i++];
            }
            else{
                // 取较小的那个放入临时数组，保证稳定性 <=
                sortedArray[count++] = (target[i] <= target[j]) ? target[i++] : target[j++];
            }
        }
        
        // 将排序好的临时数组复制回原数组的对应位置
        for(int k=0; k<n; k++){
            target[left + k] = sortedArray[k];
        }
    }

    // [递归分治] Divide
    static void divide(std::vector<int>& target, int left, int right){
        if(left >= right){
            return;
        }
        int mid = (left + right) / 2;
        // 递归左半部分
        divide(target, left, mid);
        // 递归右半部分
        divide(target, mid+1, right);
        // 合并结果
        merge(target, left, right, mid);
    }

    void mergeSort(std::vector<int>& target){
        if (target.empty()) return;
        divide(target, 0, target.size() - 1);
    }
}
