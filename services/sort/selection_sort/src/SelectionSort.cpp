#include "SelectionSort.h"
#include <algorithm>

namespace HandCreateDSA {
    void selectionSort(std::vector<int>& target){
        int n = target.size();
        for(int i=0; i<n-1; i++){
            // [寻找最小值]
            // 假设当前位置 i 是最小值，然后在 i 之后寻找更小的值
            int min_index = i;
            for(int j=i+1; j<n; j++){
                if(target[j] < target[min_index]){
                    min_index = j;
                }
            }
            // [交换]
            // 只有当最小值下标不是 i 时才进行交换
            if(min_index != i){
                std::swap(target[i], target[min_index]);
            }
        }
    }
}
