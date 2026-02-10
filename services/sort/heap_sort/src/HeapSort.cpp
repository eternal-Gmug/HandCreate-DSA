#include "HeapSort.h"
#include "Logger.h"
#include <algorithm>

namespace HandCreateDSA {
    
    // [辅助函数] 堆化
    // 维护堆的性质
    // n: 堆的大小
    // i: 当前需要堆化的节点索引
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i; // 初始化最大值为根
        int l = 2 * i + 1; // 左子节点
        int r = 2 * i + 2; // 右子节点

        // 如果左子节点比根大
        if (l < n && arr[l] > arr[largest])
            largest = l;

        // 如果右子节点比目前最大的还大
        if (r < n && arr[r] > arr[largest])
            largest = r;

        // 如果最大值不是根
        if (largest != i) {
            std::swap(arr[i], arr[largest]);

            // 递归地堆化受影响的子树
            heapify(arr, n, largest);
        }
    }

    void heapSort(std::vector<int>& target){
        int n = target.size();

        // [构建大顶堆]
        // 从最后一个非叶子节点开始，自下而上进行堆化
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(target, n, i);

        // [排序]
        // 一个个从堆顶取出元素
        for (int i = n - 1; i > 0; i--) {
            // 将当前最大的元素（堆顶）移到数组末尾
            std::swap(target[0], target[i]);

            // 对剩余的元素重新堆化，找出新的最大值
            heapify(target, i, 0);
        }
    }
}
