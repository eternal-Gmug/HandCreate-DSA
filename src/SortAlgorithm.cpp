#include "SortAlgorithm.h"

/*
选择排序算法（SelectionSort）
最坏时间复杂度O(N^2)
最好时间复杂度O(N^2)
空间复杂度O(1)
不稳定：排序后的数组可能会改变相同元素的相对位置
优点：
（1）实现简单，代码简单易懂
（2）原地排序，不需要占用额外的内存空间
（3）适合小规模的数据
缺点：
O(N^2)复杂度不适合大规模数据的排序
不稳定排序算法会改变数组相同数值元素的相对顺序
*/
void SortAlgorithm::selectionSort(){
    int n = pending.size();
    for(int i=0; i<n-1; i++){
        int min_index = i;
        // 在未排序的子数组中选择最小的元素，注意比较的数一定是遍历过程中未排序子数组里最小的数
        for(int j=i+1; j<n; j++){
            if(pending[j] < pending[min_index]){
                min_index = j;
            }
        }
        if(min_index != i){
            swap(pending[i], pending[min_index]);
        }
    }
}

void SortAlgorithm::selectionSort(vector<int>& target){
    int n = target.size();
    for(int i=0; i<n-1; i++){
        int min_index = i;
        for(int j=i+1; j<n; j++){
            if(target[j] < target[i]){
                min_index = j;
            }
        }
        if(min_index != i){
            swap(target[i], target[min_index]);
        }
    }
}

/*
冒泡排序算法（BubbleSort）
最坏时间复杂度O(N^2)
最好时间复杂度O(N^2)
空间复杂度O(1)
稳定：在排序时不会改变相同元素的相对位置
优点与选择排序类似
缺点：
（1）效率较低，不适合大规模数据的排序
（2）对于正序排序的列表会造成多余重复的比较，效率极低
*/
void SortAlgorithm::bubbleSort(){
    int n = pending.size();
    for(int j=n-1; j>0; j--){
        for(int i=0; i<j; i++){
            // 如果左边的数比右边的数大，则交换位置
            if(pending[i] > pending[i+1]){
                swap(pending[i], pending[i+1]);
            }
        }
    }
}

void SortAlgorithm::bubbleSort(vector<int>& target){
    int n = target.size();
    for(int j=n-1; j>0; j--){
        for(int i=0; i<j; i++){
            if(target[i] > target[i+1]){
                swap(target[i], target[i+1]);
            }
        }
    }
}

/*
插入排序算法（InsertionSort）
最坏时间复杂度O(N^2)
最好时间复杂度O(N)，出现在已经排好序的情况
空间复杂度O(1)
稳定：不会改变相同元素的相对位置
适用场景：数据量较小并且大部分已经排好序的情况
经常用作快速排序和归并排序的辅助算法
*/
void SortAlgorithm::insertionSort(){
    int n = pending.size();
    // 从第二个开始，假设第一个已经排好序
    for(int i=1; i<n; i++){
        int insertNum = pending[i];
        // 从已排序的数组中从后往前寻找插入的位置
        int j = i - 1;
        // 这里比较的数是insertNum而不是pending[i]，因为pending[i]会在第一轮循环中被覆盖
        while(j>=0 && pending[j] > insertNum){
            pending[j+1] = pending[j];
            j--;
        }
        pending[j+1] = insertNum;
    }
}

void SortAlgorithm::insertionSort(vector<int>& target){
    int n = target.size();
    for(int i=1; i<n; i++){
        int insertNum = target[i];
        int j = i - 1;
        while(j>=0 && target[j] > insertNum){
            target[j+1] = target[j];
            j--;
        }
        target[j+1] = insertNum;
    }
}

/*
插入排序优化版本——拆半插入
言简意赅，在寻找插入位置时从原先的逐一比较变成二分比较
这种优化手段能够将比较的时间复杂度从O(N^2)降至O(NlogN)，操作的时间复杂度依旧是O(N^2)
但这种优化非常有限，只会在比较开销大于操作开销时才显著
 */
void SortAlgorithm::insertionSort_optimization(){
    int n = pending.size();
    for(int i=1; i<n; i++){
        int insertNum = pending[i];
        // 这里使用二分比较法
        int left = 0;
        int right = i - 1;
        // 这里需要等于的原因在于需要比较重合的值与插入值的大小，确保插入值插入到正确的位置上
        while(left <= right){
            int mid = (left + right)/2;
            if(pending[mid] > insertNum){
                right = mid - 1;
            }else{    // 这里等于的情况也向右移一位，保证稳定性
                left = mid + 1;
            }
        }
        /*
        这里有个疑问，为什么left就是插入点？
        当left==right时，重合值大于插入值，插入点就在这个重合值上
        重合值小于等于插入值时，插入点就在重合点下一个位置
        无论如何都是left
        */
        // 将[left,i-1]位置的元素都向右移动一格
        for (int j=i-1; j>=left; j--){
            pending[j+1] = pending[j];
        }
        pending[left] = insertNum;
    }
}

void SortAlgorithm::insertionSort_optimization(vector<int>& target){
    int n = target.size();
    for(int i=1; i<n; i++){
        int insertNum = target[i];
        int left = 0;
        int right = i - 1;
        while(left <= right){
            int mid = (left + right)/2;
            if(target[mid] > insertNum){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
        for (int j=i-1; j>=left; j--){
            target[j+1] = target[j];
        }
        target[left] = insertNum;
    }
}

/*
希尔排序算法（ShellSort）
*/
void SortAlgorithm::shellSort(){
    // TODO: 实现希尔排序
}

void SortAlgorithm::shellSort(vector<int>& target){
    // TODO: 实现希尔排序
}

void SortAlgorithm::mergeSort(){
    // TODO: 实现归并排序
}

void SortAlgorithm::mergeSort(vector<int>& target){
    // TODO: 实现归并排序
}

void SortAlgorithm::quickSort(){
    // TODO: 实现快速排序
}

void SortAlgorithm::quickSort(vector<int>& target){
    // TODO: 实现快速排序
}

void SortAlgorithm::heapSort(){
    // TODO: 实现堆排序
}

void SortAlgorithm::heapSort(vector<int>& target){
    // TODO: 实现堆排序
}

void SortAlgorithm::countingSort(){
    // TODO: 实现计数排序
}

void SortAlgorithm::countingSort(vector<int>& target){
    // TODO: 实现计数排序
}

void SortAlgorithm::bucketSort(){
    // TODO: 实现桶排序
}

void SortAlgorithm::bucketSort(vector<int>& target){
    // TODO: 实现桶排序
}

void SortAlgorithm::radixSort(){
    // TODO: 实现基数排序
}

void SortAlgorithm::radixSort(vector<int>& target){
    // TODO: 实现基数排序
}

void SortAlgorithm::traverse(){
    int n = pending.size();
    for(int i=0; i<n; i++){
        cout<<pending[i]<<" ";
    }
}

void SortAlgorithm::traverse(vector<int>& target){
    int n = target.size();
    for(int i=0; i<n; i++){
        cout<<target[i]<<" ";
    }
}

vector<int>& SortAlgorithm::getPending(){
    return pending;
}

void SortAlgorithm::test(){
    cout<<"hello,world"<<endl;
}