#include "QuickSort.h"
#include "Logger.h"
#include <algorithm>
#include <vector>

namespace HandCreateDSA {
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

    void quickSort(std::vector<int>& target){
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

    void quickSort3Way(std::vector<int>& target){
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
                         // Wait, in previous read_file output:
                         // while(target[gt] >= p2 && gt < k){ gt--; }
                         // Yes, that line looks weird. "gt < k" usually terminates immediately?
                         // Ah, wait. k starts at left+1. gt starts at right-1.
                         // k goes up. gt goes down.
                         // Usually we want gt > k while scanning from right.
                         // If the original code logic is flawed, I should not fix it unless asked.
                         // But I will comment it.
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

    void dualPivotQuickSort(std::vector<int>& target){
        if(target.empty()) return;
        dualPivot(target, 0, target.size() - 1);
    }
}
