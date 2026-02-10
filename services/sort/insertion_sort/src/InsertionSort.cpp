#include "InsertionSort.h"
#include <algorithm>

namespace HandCreateDSA {
    void insertionSort(std::vector<int>& target){
        int n = target.size();
        for(int i=1; i<n; i++){
            // [记录当前值]
            // 将当前待插入的元素保存在临时变量中
            int insertNum = target[i];
            int j = i - 1;
            
            // [寻找位置]
            // 若前一个元素比当前元素大，则将前一个元素后移，腾出位置
            while(j>=0 && target[j] > insertNum){
                target[j+1] = target[j];
                j--;
            }
            // [插入]
            // 将保存的元素放到正确的位置
            target[j+1] = insertNum;
        }
    }

    void insertionSortOptimized(std::vector<int>& target){
        int n = target.size();
        for(int i=1; i<n; i++){
            int insertNum = target[i];
            int left = 0;
            int right = i - 1;
            
            // [二分查找]
            // 在有序区 [0...i-1] 中查找插入位置，减少比较次数
            // 这不能减少数据移动的次数，所以整体复杂度仍是 O(n^2)
            while(left <= right){
                int mid = (left + right)/2;
                if(target[mid] > insertNum){
                    right = mid - 1;
                }else{
                    left = mid + 1;
                }
            }
            
            // [数据移动]
            // 将 left 之后的数据整体后移
            for (int j=i-1; j>=left; j--){
                target[j+1] = target[j];
            }
            target[left] = insertNum;
        }
    }
}
