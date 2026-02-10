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
增量序列使用希尔增量（n/2,n/4,...,1）
希尔排序是插入排序的改进版本，充分利用插入排序在有序状态下的线性效率
最坏时间复杂度O(N^2)
最好时间复杂度O(NlogN) 增量序列选择得当
空间复杂度O(1)
不稳定：会改变相同元素的相对位置
适合用作复杂排序算法的预处理排序
*/
void SortAlgorithm::shellSort(){
    int n = pending.size();
    int gap = n/2;
    while(gap > 0){
        // 对每个子列表进行插入排序
        for(int i=gap; i<2*gap; i++){
            // 内部单个子列表进行排序
            for(int j=i; j<n; j+=gap){
                // 寻找插入的位置
                int insertNum = pending[j];
                int k = j - gap;
                while(k>=0 && pending[k] > insertNum){
                    pending[k + gap] = pending[k];
                    k -= gap;
                }
                pending[k+gap] = insertNum;
            }
        }
        gap /= 2;
    }
}

void SortAlgorithm::shellSort(vector<int>& target){
    int n = target.size();
    int gap = n/2;
    while(gap > 0){
        for(int i=gap; i<2*gap; i++){
            for(int j=i; j<n; j+=gap){
                int insertNum = target[j];
                int k = j - gap;
                while(k>=0 && target[k] > insertNum){
                    target[k + gap] = target[k];
                    k -= gap;
                }
                target[k+gap] = insertNum;
            }
        }
        gap /= 2;
    }
}

/*
归并排序算法（MergeSort）
归并排序是典型的分治思想的应用，它通过将一个大数组一分而二，先处理左数组的排序，再处理右数组的排序，最后将左右数组给合并成一个新数组
时间复杂度分析：
（1）将一个大数组拆分成单元素数组，需要logN的复杂度
（2）在合并数组的过程中，需要对分数组每一个元素进行比较，需要N的复杂度
（3）总共复杂度为O(NlogN)
空间复杂度分析：
（1）在合并排序的过程中，需要给它分配一个额外的空间记录已排好序的元素，复杂度为O(N)
稳定性分析：
稳定，不会改变相同元素的相对位置
适用场景：
适用于大规模数据与外部排序（对磁盘文件进行排序）
对于小规模数据，递归的思路可能还不如插入排序、冒泡排序来得效率高
*/
// 将两个数组合并在一起
void merge(vector<int>& pending, int left, int right, int mid){
    // 先预分配一个大小相等的已排序数组空间
    int n = right - left + 1;
    vector<int> sortedArray(n,0);
    int i = left;
    int j = mid + 1;
    int count = 0;       // 已排序数组内的元素个数
    while(count < n){
        // 如果左边数组已经遍历完
        if(i > mid){
            sortedArray[count++] = pending[j++];
        }
        // 如果右边数组已经遍历完
        else if(j > right){
            sortedArray[count++] = pending[i++];
        }
        else{
            sortedArray[count++] = (pending[i] <= pending[j])?pending[i++]:pending[j++];
        }
    }
    // 需要将sortedArray重新复写到pending上
    for(int k=0; k<n; k++){
        pending[left + k] = sortedArray[k];
    }
}

// 分解大数组
void divide(vector<int>& pending, int left, int right){
    if(left >= right){
        return;
    }
    // 寻找分解点，如果个数是偶数则对称，如果个数是奇数，左边的数组个数比右边的多一个
    int mid = (left + right) / 2;
    divide(pending, left, mid);
    divide(pending, mid+1, right);
    merge(pending, left, right, mid);
}

void SortAlgorithm::mergeSort(){
    divide(pending, 0, pending.size() - 1);
}

void SortAlgorithm::mergeSort(vector<int>& target){
    divide(target, 0, target.size() - 1);
}

/*
快速排序算法（QuickSort）
选取一个基准元素，寻找这个基准元素的位置使得左边都比基准元素小、右边都比基准元素大
时间复杂度分析：
（1）最坏情况（数组已经排好序的情况）：O(N^2)
（2）最好情况（每次分治两边的数组容量差不多大）：O(NlogN)
空间复杂度分析：
原地排序算法，复杂度为O(logN)，递归栈的调用
稳定性：
不稳定，会改变相同元素的相对位置
适用场景：
处理大规模随机元素数组，效率高，作为sort函数的通用排序算法
但对于小规模数据的排序效率较低
*/
// （优化点1😊）三数取中选取基准数——针对数组近乎有序导致复杂度逼近O(N^2)的难点
void getMediumNum(vector<int>& pending, int left, int right){
    int mid = (left + right) / 2;
    int min_index = left;     // 记录最小基准数的索引，初始化为left
    // 比较left和mid的大小
    if(pending[mid] < pending[min_index]){
        min_index = mid;
    }
    // 比较right和min(left,mid)的大小
    if(pending[right] < pending[min_index]){
        return;
    }
    // 最小值与最后一个元素交换位置
    swap(pending[min_index], pending[right]);
}

// 寻找基准元素所在的位置
// 这里先把最后一个元素作为我的基准元素
int SearchPivotPosition(vector<int>& pending, int left, int right){
    // 使用三数取中优化基准数的选择
    getMediumNum(pending, left, right);
    // 将最后一个元素作为基准元素
    int pivot = pending[right];
    // 定义遍历双指针
    int i = left;
    int j = right;
    while(i < j){
        // 从左边开始寻找比pivot大的数
        while(i < j && pending[i] <= pivot){
            i++;
        }
        pending[j] = pending[i];
        // 从右边开始寻找比pivot小的数
        while(i < j && pending[j] >= pivot){
            j--;
        }
        pending[i] = pending[j];
    }
    pending[i] = pivot;
    return i;
}

// 快速排序递归体
void innerQuick(vector<int>& pending, int left, int right){
    if(left >= right){
        return;
    }
    int pivotPos = SearchPivotPosition(pending, left, right);
    innerQuick(pending, left, pivotPos - 1);
    innerQuick(pending, pivotPos + 1, right);
}

void SortAlgorithm::quickSort(){
    innerQuick(pending, 0, pending.size() - 1);
}

void SortAlgorithm::quickSort(vector<int>& target){
    innerQuick(target, 0, target.size() - 1);
}

/*
（优化点2😊）三向切分快速排序算法（3-Way QuickSort）—— 针对具有大量重复元素导致递归树不平衡的问题
将数组分为三部分：小于基准、等于基准、大于基准
对于包含大量重复元素的数组，效率远优于普通快速排序
传统快速排序会导致重复元素在递归树中不平衡，比如当一个数组内的元素全部相同，复杂度可能飙至O(N^2)
时间复杂度：O(NlogN)，大量重复元素时接近O(N)
空间复杂度：O(logN)递归栈
不稳定
*/
void innerQuick3Way(vector<int>& pending, int left, int right){
    if(left >= right){
        return;
    }
    int lt = left;   // 左边界值，保证[left,lt-1]的值都小于基准值
    int gt = right;  // 右边界值，保证[gt+1,right]的值都大于基准值
    int k = lt + 1;   // 遍历指针，从左边界的下一个元素开始遍历
    int pivot = pending[left];      // 选取第一个值作为基准值
    while(k <= gt){
        if(pending[k] < pivot){
            /* 
            这里k和lt都自增的原因在于交换后的lt一定比pivot小，为了保证lt的左边元素都小于pivot
            k自增的原因在于交换的lt一定等于基准值，交换后不需要管什么，直接遍历下一个元素
            */
            swap(pending[k++], pending[lt++]);
        }else if(pending[k] > pivot){
            /*
            这里gt需要自减的原因在于交换后的gt一定比pivot大，为了保证gt的右边元素都大于pivot
            k不需要自增的原因在于原来gt的值是不确定的，交换后需要重新判断
            */
            swap(pending[k], pending[gt--]);
        }else{
            // 如果等于基准值，让遍历指针向右移一位即可
            k++;
        }
    }
    // 此时[left,lt-1]的值都小于基准值，[lt,gt]的值都等于基准值，[gt+1,right]的值都大于基准值
    // 对[left,lt-1]和[gt+1,right]重复上述过程
    innerQuick3Way(pending, left, lt - 1);
    innerQuick3Way(pending, gt + 1, right);
}

void SortAlgorithm::quickSort3Way(){
    innerQuick3Way(pending, 0, pending.size() - 1);
}

void SortAlgorithm::quickSort3Way(vector<int>& target){
    innerQuick3Way(target, 0, target.size() - 1);
}

/*
（优化点3😊）双枢轴快速排序算法（Dual-Pivot QuickSort）
传统的快速排序是“二分天下”，那么双枢轴快速排序就是“三足鼎立”
选择两个基准数p1，p2，将分区划分成小于p1、[p1,p2]、大于p2三个分区
递归树的高度从log2N降成log3N
时间复杂度也相应从O(NlogN)降至O(Nlog3N)
双枢轴快速排序契合CPU的缓存局限性，同时处理大量相同元素时更加稳定
双枢轴快速排序是Arrays.sort()的默认排序方式
*/
void dualPivot(vector<int>& pending, int left, int right){
    if(left >= right){
        return;
    }
    // 保证数组的首元素要小于等于末元素
    if(pending[left] > pending[right]){
        swap(pending[left], pending[right]);
    }
    // 定义两个基准数p1和p2
    int p1 = pending[left];
    int p2 = pending[right];
    // 定义边界
    int lt = left + 1;       // [left,lt-1]是小于p1的元素
    int gt = right - 1;      // [gt+1,right]是大于p2的元素
    int k = left + 1;    // 从左边界开始遍历
    while(k <= gt){
        if(pending[k] < p1){
            swap(pending[lt++], pending[k++]);
        }else if(pending[k] >= p2){
            // 寻找右区第一个小于p2的元素
            while(pending[gt] >= p2 && gt < k){
                gt--;
            }
            swap(pending[gt--], pending[k]);
            // 判断交换的元素是否小于p1
            if(pending[k] < p1){
                swap(pending[lt++], pending[k++]);
            }
        }else{   // 如果p1<=x<p2遍历下一个元素，将它留到中区
            k++;
        }
    }
    // 此时lt指向的是大于等于p1的值，gt指向的小于p2的值，还不能直接交换
    lt--;
    gt++;
    swap(pending[left], pending[lt]);
    swap(pending[right], pending[gt]);
    // 对左中右三个区做递归处理
    dualPivot(pending, left, lt - 1);
    dualPivot(pending, lt + 1, gt - 1);
    dualPivot(pending, gt + 1, right);
}

void SortAlgorithm::dualPivotQuickSort(){
    dualPivot(pending, 0, pending.size() - 1);
}

void SortAlgorithm::dualPivotQuickSort(vector<int>& target){
    dualPivot(target, 0, target.size() - 1);
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
