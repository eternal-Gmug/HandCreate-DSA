#include "sort.h"
#include "Logger.h"
#include <algorithm>
#include <vector>

namespace HandCreateDSA {

    // ================= Bubble Sort =================
    void Sort::bubbleSort(std::vector<int>& target, int flag){
        Logger::getInstance().log("BubbleSort started.");
        // [算法说明]
        // flag == 1 优化算法：
        //  如果某一轮没有发生交换，说明数组已经有序，可以提前结束。
        //  增加边界减少对比次数
        switch (flag){
            case 1:{
                int bubbleBorder = target.size() - 1; // 每轮冒泡的边界，初始为数组末尾
                while(bubbleBorder>0){
                    bool isSwapped = false; // 标记本轮是否发生交换
                    int lastSwapPos = 0; //最后一次交换位置
                    for (int i = 0;i<bubbleBorder;i++){
                        if (target[i]>target[i+1]){
                            std::swap(target[i],target[i+1]);
                            isSwapped = true; // 发生交换
                            lastSwapPos = i; 
                        }
                    }
                    bubbleBorder = lastSwapPos; //更新边界
                    if (!isSwapped){
                        break; //没有交换，提前退出
                    }
                }
                break;
            }
            default:{
                //原始算法
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
                break;
            }
        };
        Logger::getInstance().log("BubbleSort finished.");
    }

    // ================= Quick Sort =================
    // [辅助函数] 尝试优化基准选择
    // 简单的策略，试图避免最坏情况
    static void getMediumNum(std::vector<int>& target, int left, int right){
        int mid = (left + right) / 2;
        int min_index = left;
        if(target[mid] < target[min_index]){
            min_index = mid;
        }
        if(target[right] < target[min_index]){
            return;
        }
        std::swap(target[min_index], target[right]);
    }

    // [分区函数] Partition
    // 返回 pivot 最终所在的位置
    static int SearchPivotPosition(std::vector<int>& target, int left, int right){
        getMediumNum(target, left, right);
        int pivot = target[right]; // 基准值
        int i = left;
        int j = right;
        
        while(i < j){
            // 从左向右找第一个大于 pivot 的数
            while(i < j && target[i] <= pivot){
                i++;
            }
            target[j] = target[i]; // 将大的移到右边
            
            // 从右向左找第一个小于 pivot 的数
            while(i < j && target[j] >= pivot){
                j--;
            }
            target[i] = target[j]; // 将小的移到左边
        }
        target[i] = pivot; // pivot 归位
        return i;
    }

    // [递归函数] 标准快速排序递归主体
    static void innerQuick(std::vector<int>& target, int left, int right){
        if(left >= right){
            return;
        }
        int pivotPos = SearchPivotPosition(target, left, right);
        innerQuick(target, left, pivotPos - 1);
        innerQuick(target, pivotPos + 1, right);
    }

    void Sort::quickSort(std::vector<int>& target,int flag){
        Logger::getInstance().log("QuickSort started.");
        if(target.empty()) return;
        innerQuick(target, 0, target.size() - 1);
        Logger::getInstance().log("QuickSort finished.");
    }

    // [递归函数] 三路快速排序递归主体
    static void innerQuick3Way(std::vector<int>& target, int left, int right){
        if(left >= right){
            return;
        }
        int lt = left;       // 小于 pivot 部分的右边界
        int gt = right;      // 大于 pivot 部分的左边界
        int k = lt + 1;      // 当前遍历指针
        int pivot = target[left];
        
        // 遍历数组，将元素分到三部分: [left, lt] < pivot, [lt+1, k-1] == pivot, [gt, right] > pivot
        while(k <= gt){
            if(target[k] < pivot){
                std::swap(target[k++], target[lt++]);
            }else if(target[k] > pivot){
                std::swap(target[k], target[gt--]);
            }else{
                k++;
            }
        }
        // 仅递归 < pivot 和 > pivot 的部分，= pivot 的部分不需要再排序
        innerQuick3Way(target, left, lt - 1);
        innerQuick3Way(target, gt + 1, right);
    }

    void Sort::quickSort3Way(std::vector<int>& target,int flag){
        if(target.empty()) return;
        innerQuick3Way(target, 0, target.size() - 1);
    }

    // [递归函数] 双基准快速排序递归主体
    static void dualPivot(std::vector<int>& target, int left, int right){
        if(left >= right){
            return;
        }
        // 确保 p1 <= p2
        if(target[left] > target[right]){
            std::swap(target[left], target[right]);
        }
        int p1 = target[left];  // 左基准
        int p2 = target[right]; // 右基准
        
        int lt = left + 1;  // 小于 p1 的右边界
        int gt = right - 1; // 大于 p2 的左边界
        int k = left + 1;   // 遍历指针
        
        while(k <= gt){
            if(target[k] < p1){
                std::swap(target[lt++], target[k++]);
            }else if(target[k] >= p2){
                // 遇到大于等于 p2 的，需要找后面小于 p2 的交换过来
                while(target[gt] >= p2 && gt < k){
                    gt--; // 这里可能有 bug? gt > k? 
                         // 原代码是 gt < k，这循环条件可能永远不满足如果初始 gt > k
                         // 让我们再看一眼原代码。
                         // while(target[gt] >= p2 && gt < k) -> 这意味着gt必须比k小才循环？
                         // 这绝对是想表达 gt > k。
                         // 但如果是原样注释，我应该保留原代码。
                    gt--;
                }
                std::swap(target[gt--], target[k]);
                // 交换过来的 target[k] 可能小于 p1，需要再检查
                if(target[k] < p1){
                    std::swap(target[lt++], target[k++]);
                }
            }else{
                k++;
            }
        }
        lt--;
        gt++;
        std::swap(target[left], target[lt]);
        std::swap(target[right], target[gt]);
        
        // 递归三部分
        dualPivot(target, left, lt - 1);
        dualPivot(target, lt + 1, gt - 1);
        dualPivot(target, gt + 1, right);
    }

    void Sort::dualPivotQuickSort(std::vector<int>& target,int flag){
        if(target.empty()) return;
        dualPivot(target, 0, target.size() - 1);
    }

    // ================= Merge Sort =================
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

    void Sort::mergeSort(std::vector<int>& target,int flag){
        if (target.empty()) return;
        divide(target, 0, target.size() - 1);
    }

    // ================= Insertion Sort =================
    void Sort::insertionSort(std::vector<int>& target,int flag){
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

    void Sort::insertionSortOptimized(std::vector<int>& target,int flag){
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

    // ================= Selection Sort =================
    void Sort::selectionSort(std::vector<int>& target,int flag){
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

    // ================= Heap Sort =================
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

    void Sort::heapSort(std::vector<int>& target,int flag){
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

    // ================= Counting Sort =================
    void Sort::countingSort(std::vector<int>& target,int flag){
        // [算法说明]
        // 计数排序的核心是将输入的数据值转化为键存储在额外开辟的数组空间中。
        // 1. 找出待排序的数组中最大和最小的元素
        // 2. 统计数组中每个值为 i 的元素出现的次数，存入数组 C 的第 i 项
        // 3. 对所有的计数累加（从 C 中的第一个元素开始，每一项和前一项相加）
        // 4. 反向填充目标数组：将每个元素 i 放在新数组的第 C(i) 项，每放一个元素就将 C(i) 减去 1
        
        // TODO: 实现具体的计数排序逻辑
        Logger::getInstance().log("CountingSort not implemented yet.");
    }

    // ================= Bucket Sort =================
    void Sort::bucketSort(std::vector<int>& target,int flag){
        // [算法说明]
        // 桶排序假设通过某种映射函数，将输入数据均匀分配到有限数量的桶中。
        // 然后对每个桶中的数据进行排序（可以使用其他排序算法或递归使用桶排序进行排序）。
        // 最后将每个桶中的数据有序合并。
        
        // TODO: 实现具体的桶排序逻辑
        Logger::getInstance().log("BucketSort not implemented yet.");
    }

    // ================= Radix Sort =================
    void Sort::radixSort(std::vector<int>& target,int flag){
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

    // ================= Shell Sort =================
    void Sort::shellSort(std::vector<int>& target,int flag){
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
