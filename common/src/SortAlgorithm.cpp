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
    int min_index_lm = left;     // 记录left和mid之间最小基准数的索引，初始化为left
    int max_index_lm = mid;      // 记录left和mid之间最大基准数的索引，初始化位mid
    // 比较left和mid的大小
    if(pending[left] > pending[mid]){
        min_index_lm = mid;
        max_index_lm = left;
    }
    // 比较right和min_index_lm的大小
    if(pending[min_index_lm] > pending[right]){
        swap(pending[min_index_lm], pending[right]);
        return;
    }
    // 比较right和max_index_lm的大小
    if(pending[max_index_lm] < pending[right]){
        swap(pending[max_index_lm], pending[right]);
    }
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
            while(pending[gt] >= p2 && gt > k){
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

/*
堆排序算法（Heap Sort）
堆排序通过对数组构建大根堆，每次将堆顶元素与末尾元素交换并逐步缩小处理数组的大小以达到有序的状态
时间复杂度分析：
（1）对每个元素构建大根堆时操作的复杂度是logN
（2）需要对每个非叶子节点调整位置，复杂度是N
（3）总共的复杂度是O(NlogN)
空间复杂度分析：
堆的本质还是在数组上操作，原地排序，复杂度是O(1)
稳定性：
不稳定，存在大量树状父子节点的交换会改变相同元素的相对位置
适用场景：
适合内存排序，适合处理大规模数据排序的场景，但在小规模场景下性能可能不如插入排序
*/
void heapBuild(vector<int>& pending, int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // 父节点与左结点比较
    if(left < n && pending[left] > pending[largest]){
        largest = left;
    }
    // 右节点与min(左节点，父节点)比较
    if(right < n && pending[right] > pending[largest]){
        largest = right;
    }
    // 如果最大值发生了改变
    if(largest != i){
        swap(pending[i], pending[largest]);
        // 因为上层构建时会打乱下层已构建好的大根堆，所以需要进行延续处理
        heapBuild(pending, n, largest);
    }
}

void SortAlgorithm::heapSort(){
    int n = pending.size();
    // 从最后一个非叶子节点构建大根堆
    for(int i=(n / 2 - 1); i>=0; i--){
        heapBuild(pending, n, i);
    }
    // 构建完之后将末尾元素与堆顶元素交换
    for(int i=n-1; i>0; i--){
        swap(pending[i], pending[0]);
        // 交换完以后将堆的大小减去1并且对根顶元素重新构建
        heapBuild(pending, i, 0);
    }
}

void SortAlgorithm::heapSort(vector<int>& target){
    int n = target.size();
    // 从最后一个非叶子节点构建大根堆
    for(int i=(n/2-1); i>=0; i--){
        heapBuild(target, n, i);
    }
    // 交换数组末尾元素与堆顶元素
    for(int i=n-1; i>0; i--){
        swap(pending[i], pending[0]);
        // 针对堆顶元素重新构建大根堆，但堆的大小需要减去1
        heapBuild(target, i, 0);
    }
}

/*
计数排序算法（CountingSort）
计数排序不是比较型算法，原理非常简单，对每个元素记录它出现的次数，要求必须有明确的数字范围❗
时间复杂度分析：
（1）统计频率，需要遍历一遍数组，复杂度为N
（2）遍历累加数组并复写到原数组上，复杂度为K和N
（3）总的复杂度是O(N+K)，N是数组的大小，K是数字范围的大小
空间复杂度分析：
（1）需要额外开一个大小为K的数组，复杂度为O(K) ——— 直接复写回原数组的情况下
稳定性分析：
因为是顺序遍历，相同元素会按照一样的相对位置落入计数数组中
注意：这种排序仅适用于整数且有限范围内的数据
适用场景：
（1）排序范围较小的整数数组
（2）适合外部排序（磁盘文件）
*/
void SortAlgorithm::countingSort(){
    auto min_index = min_element(pending.begin(), pending.end());
    auto max_index = max_element(pending.begin(), pending.end());
    int min_num = *min_index;
    int max_num = *max_index;
    int capacity = max_num - min_num + 1;
    vector<int> record(capacity, 0);
    int n = pending.size();
    // 计算元素出现次数
    for(int i=0; i<n; i++){
        record[pending[i] - min_num]++;
    }
    // 根据record记录的值复写回pending中
    int i = 0;      // pending的复写指针
    for(int j=0; j<capacity; j++){
        while(record[j] > 0){
            pending[i++] = j + min_num;
            record[j]--;
        }
    }
}

void SortAlgorithm::countingSort(vector<int>& target){
    auto min_index = min_element(target.begin(), target.end());
    auto max_index = max_element(target.begin(), target.end());
    int min_num = *min_index;
    int max_num = *max_index;
    int capacity = max_num - min_num + 1;
    vector<int> record(capacity, 0);
    int n = target.size();
    for(int i=0; i<n; i++){
        record[target[i] - min_num]++;
    }
    int i = 0;
    for(int j=0; j<capacity; j++){
        while(record[j] > 0){
            target[i++] = j + min_num;
            record[j]--;
        }
    }
}

/*
桶排序算法（BucketSort）
桶排序是一种分布式排序算法，它利用函数的映射关系将输入数据分配到不同的桶中，在这个桶里面进行排序，最后再进行合并
当数据分布均匀时，排序的性能优异，如果不均匀的话，容易造成大量空桶的存在
时间复杂度分析：
（1）将每个元素塞进对应的桶里，复杂度是N
（2）假设每个桶里的元素个数是m，并且使用快速排序进行排序，那么K个桶的时间复杂度是O(K*mlogm)
（3）再将每个桶里的元素顺序合并，复杂度是N
（4）总的时间复杂度为O(N + K*mlogm)
空间复杂度分析：
需要额外K个vector来记录每个vector待排序的元素，复杂度是O(N+K)
适用场景：
桶排序是典型的分布式排序算法，广泛应用于外部排序，例如加载一个超大乱序文件时，可以将它拆分到有限的顺序文件中进行排序整理，最后再合并成一个完整的文件
*/
void SortAlgorithm::bucketSort(int bucketSize){
    int n = pending.size();
    if(n <= 1) return;
    int minVal = *min_element(pending.begin(), pending.end());
    int maxVal = *max_element(pending.begin(), pending.end());
    // 计算桶的数量
    int bucketCount = (maxVal - minVal) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount);
    // 将元素分配到对应的桶中
    for(int i=0; i<n; i++){
        int index = (pending[i] - minVal) / bucketSize;
        buckets[index].push_back(pending[i]);
    }
    // 对每个桶内部进行排序，然后合并回原数组
    int pos = 0;
    for(int i=0; i<bucketCount; i++){
        // 桶内使用快速排序
        quickSort(buckets[i]);
        // 将桶内元素复写回原数组
        for(int j=0; j<(int)buckets[i].size(); j++){
            pending[pos++] = buckets[i][j];
        }
    }
}

void SortAlgorithm::bucketSort(vector<int>& target, int bucketSize){
    int n = target.size();
    if(n <= 1) return;
    int minVal = *min_element(target.begin(), target.end());
    int maxVal = *max_element(target.begin(), target.end());
    int bucketCount = (maxVal - minVal) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount);
    for(int i=0; i<n; i++){
        int index = (target[i] - minVal) / bucketSize;
        buckets[index].push_back(target[i]);
    }
    int pos = 0;
    for(int i=0; i<bucketCount; i++){
        quickSort(buckets[i]);
        for(int j=0; j<(int)buckets[i].size(); j++){
            target[pos++] = buckets[i][j];
        }
    }
}

/*
基数排序算法（RadixSort）
基数排序是一种非比较型排序算法，它通过从最低位到最高位按位排序来达到有序的状态
基数排序是一种对非负整数处理的排序算法，如果数组中存在负数，可以通过负数偏移或正负数组分开排序的方式处理
时间复杂度分析：
（1）元素个数：把每个元素按处理位放入桶中，复杂度为N
（2）轮次：按最大数的位数K来执行比较的次数，复杂度为K
（3）总的时间复杂度是O(N*K)
空间复杂度分析：
（1）需要额外的空间存储桶和桶内的元素，复杂度是O(N+K)
稳定性分析：
与桶排序类似，相同元素会按照原先的相对位置放入桶中，不会改变它们之间的相对位置
适用范围：
数字范围较小且最大数位数K不大的整数数据排序
外部排序（磁盘文件）
*/
void SortAlgorithm::radixSort(){
    int n = pending.size();
    if(n <= 1) return;
    int minVal = *min_element(pending.begin(), pending.end());
    int maxVal = *max_element(pending.begin(), pending.end());
    vector<vector<int>> bitBucket(10);
    // 为消除负数对排序的影响，如果最小值小于0，对每个元素做一个偏移处理
    if(minVal < 0){
        for(int i=0; i<n; i++){
            pending[i] -= minVal;
        }
        maxVal -= minVal;
    }
    // 确定需要遍历的轮次，即最大值的位数
    int step = 1;
    while(maxVal/(pow(10,step)) > 0){
        step++;
    }
    // 按轮次进行排序
    int cur = 1;     // 当前轮次
    while(cur <= step){
        for(int i=0; i<n; i++){
            int reminder = pending[i] % (int)pow(10,cur);
            int bitNum = reminder / (int)pow(10,cur - 1);
            bitBucket[bitNum].push_back(pending[i]);
        }
        // 将bitBucket内的数复写回pending数组中
        int pos = 0;
        for(int i=0; i<10; i++){
            for(int j=0; j < bitBucket[i].size(); j++){
                pending[pos++] = bitBucket[i][j];
            }
            bitBucket[i].clear();   // 逐个清空每个桶，而不是清空整个二维vector
        }
        cur++;
    }
    // 最后需要对负数偏移做恢复处理
    if(minVal < 0){
        for(int i=0; i<n; i++){
            pending[i] += minVal;
        }
    }
}

void SortAlgorithm::radixSort(vector<int>& target){
    int n = target.size();
    if(n <= 1) return;
    int minVal = *min_element(target.begin(), target.end());
    int maxVal = *max_element(target.begin(), target.end());
    vector<vector<int>> bitBucket(10);
    // 为消除负数对排序的影响，如果最小值小于0，对每个元素做一个偏移处理
    if(minVal < 0){
        for(int i=0; i<n; i++){
            target[i] -= minVal;
        }
        maxVal -= minVal;
    }
    // 确定需要遍历的轮次，即最大值的位数
    int step = 1;
    while(maxVal/(pow(10,step)) > 0){
        step++;
    }
    // 按轮次进行排序
    int cur = 1;     // 当前轮次
    while(cur <= step){
        for(int i=0; i<n; i++){
            int reminder = target[i] % (int)pow(10,cur);
            int bitNum = reminder / (int)pow(10,cur - 1);
            bitBucket[bitNum].push_back(target[i]);
        }
        // 将bitBucket内的数复写回target数组中
        int pos = 0;
        for(int i=0; i<10; i++){
            for(int j=0; j < bitBucket[i].size(); j++){
                target[pos++] = bitBucket[i][j];
            }
            bitBucket[i].clear();   // 逐个清空每个桶，而不是清空整个二维vector
        }
        cur++;
    }
    // 最后需要对负数偏移做恢复处理
    if(minVal < 0){
        for(int i=0; i<n; i++){
            target[i] += minVal;
        }
    }
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
