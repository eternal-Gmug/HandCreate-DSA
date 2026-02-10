#include "SortProfiler.h"
#include <filesystem>

// 获取可执行文件所在目录的上级目录（即项目根目录）
static string getProjectRoot() {
    // 获取当前工作目录作为基准
    return filesystem::current_path().string();
}

// 构造函数：初始化排序器引用和日志路径
SortProfiler::SortProfiler(SortAlgorithm& sorter, const string& logDir)
    : sorter(sorter) {
    // 使用项目根目录拼接绝对路径
    logPath = getProjectRoot() + "/" + logDir;
    // 确保日志目录存在
    filesystem::create_directories(logPath);
}

// 获取当前时间戳
string SortProfiler::getTimestamp() {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    tm localTime;
    localtime_s(&localTime, &t);
    ostringstream oss;
    oss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// 将 vector 转为可读字符串
string SortProfiler::vecToString(const vector<int>& vec) {
    ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        oss << vec[i];
        if (i < vec.size() - 1) oss << ", ";
    }
    oss << "]";
    return oss.str();
}

// 写入日志文件
void SortProfiler::writeLog(const string& algorithmName,
                             const vector<int>& before,
                             const vector<int>& after,
                             double elapsedMs) {
    string filename = logPath + "/sort_log.txt";
    ofstream logFile(filename, ios::app);
    if (!logFile.is_open()) {
        cerr << "无法打开日志文件: " << filename << endl;
        return;
    }

    logFile << "========================================" << endl;
    logFile << "时间: " << getTimestamp() << endl;
    logFile << "算法: " << algorithmName << endl;
    logFile << "数据量: " << before.size() << " 个元素" << endl;
    logFile << "排序前: " << vecToString(before) << endl;
    logFile << "排序后: " << vecToString(after) << endl;
    logFile << "耗时: " << fixed << setprecision(4) << elapsedMs << " ms" << endl;
    logFile << "========================================" << endl;
    logFile << endl;
    logFile.close();

    cout << "[SortProfiler] " << algorithmName
         << " 完成, 耗时 " << fixed << setprecision(4) << elapsedMs << " ms"
         << " (已记录到 " << filename << ")" << endl;
}

// 通用 profile 方法
void SortProfiler::profile(const string& algorithmName, function<void()> sortFunc, vector<int>& target) {
    // 保存排序前的数组副本
    vector<int> before = target;

    // 计时开始
    auto start = chrono::high_resolution_clock::now();
    sortFunc();
    auto end = chrono::high_resolution_clock::now();

    // 计算耗时（毫秒）
    double elapsed = chrono::duration<double, milli>(end - start).count();

    // 写入日志
    writeLog(algorithmName, before, target, elapsed);
}

// ========== 便捷方法：使用构造时绑定的 pending ==========

void SortProfiler::selectionSort() {
    vector<int>& pending = sorter.getPending();
    profile("选择排序 (Selection Sort)", [&]() { sorter.selectionSort(); }, pending);
}

void SortProfiler::selectionSort(vector<int>& target) {
    profile("选择排序 (Selection Sort)", [&]() { sorter.selectionSort(target); }, target);
}

void SortProfiler::bubbleSort() {
    vector<int>& pending = sorter.getPending();
    profile("冒泡排序 (Bubble Sort)", [&]() { sorter.bubbleSort(); }, pending);
}

void SortProfiler::bubbleSort(vector<int>& target) {
    profile("冒泡排序 (Bubble Sort)", [&]() { sorter.bubbleSort(target); }, target);
}

void SortProfiler::insertionSort() {
    vector<int>& pending = sorter.getPending();
    profile("插入排序 (Insertion Sort)", [&]() { sorter.insertionSort(); }, pending);
}

void SortProfiler::insertionSort(vector<int>& target) {
    profile("插入排序 (Insertion Sort)", [&]() { sorter.insertionSort(target); }, target);
}

void SortProfiler::insertionSort_optimization() {
    vector<int>& pending = sorter.getPending();
    profile("拆半插入排序 (Binary Insertion Sort)", [&]() { sorter.insertionSort_optimization(); }, pending);
}

void SortProfiler::insertionSort_optimization(vector<int>& target) {
    vector<int>& pending = sorter.getPending();
    profile("拆半插入排序 (Binary Insertion Sort)", [&]() { sorter.insertionSort_optimization(target); }, pending);
}

void SortProfiler::shellSort() {
    vector<int>& pending = sorter.getPending();
    profile("希尔排序 (Shell Sort)", [&]() { sorter.shellSort(); }, pending);
}

void SortProfiler::shellSort(vector<int>& target) {
    profile("希尔排序 (Shell Sort)", [&]() { sorter.shellSort(target); }, target);
}

void SortProfiler::mergeSort() {
    vector<int>& pending = sorter.getPending();
    profile("归并排序 (Merge Sort)", [&]() { sorter.mergeSort(); }, pending);
}

void SortProfiler::mergeSort(vector<int>& target) {
    profile("归并排序 (Merge Sort)", [&]() { sorter.mergeSort(target); }, target);
}

void SortProfiler::quickSort() {
    vector<int>& pending = sorter.getPending();
    profile("快速排序 (Quick Sort)", [&]() { sorter.quickSort(); }, pending);
}

void SortProfiler::quickSort(vector<int>& target) {
    profile("快速排序 (Quick Sort)", [&]() { sorter.quickSort(target); }, target);
}

void SortProfiler::quickSort3Way() {
    vector<int>& pending = sorter.getPending();
    profile("三向切分快速排序 (3-Way Quick Sort)", [&]() { sorter.quickSort3Way(); }, pending);
}

void SortProfiler::quickSort3Way(vector<int>& target) {
    profile("三向切分快速排序 (3-Way Quick Sort)", [&]() { sorter.quickSort3Way(target); }, target);
}

void SortProfiler::dualPivotQuickSort() {
    vector<int>& pending = sorter.getPending();
    profile("双轴快速排序 (Dual Pivot Quick Sort)", [&]() { sorter.dualPivotQuickSort(); }, pending);
}

void SortProfiler::dualPivotQuickSort(vector<int>& target) {
    profile("双轴快速排序 (Dual Pivot Quick Sort)", [&]() { sorter.dualPivotQuickSort(target); }, target);
}

void SortProfiler::heapSort() {
    vector<int>& pending = sorter.getPending();
    profile("堆排序 (Heap Sort)", [&]() { sorter.heapSort(); }, pending);
}

void SortProfiler::heapSort(vector<int>& target) {
    profile("堆排序 (Heap Sort)", [&]() { sorter.heapSort(target); }, target);
}

void SortProfiler::countingSort() {
    vector<int>& pending = sorter.getPending();
    profile("计数排序 (Counting Sort)", [&]() { sorter.countingSort(); }, pending);
}

void SortProfiler::countingSort(vector<int>& target) {
    profile("计数排序 (Counting Sort)", [&]() { sorter.countingSort(target); }, target);
}

void SortProfiler::bucketSort() {
    vector<int>& pending = sorter.getPending();
    profile("桶排序 (Bucket Sort)", [&]() { sorter.bucketSort(); }, pending);
}

void SortProfiler::bucketSort(vector<int>& target) {
    profile("桶排序 (Bucket Sort)", [&]() { sorter.bucketSort(target); }, target);
}

void SortProfiler::radixSort() {
    vector<int>& pending = sorter.getPending();
    profile("基数排序 (Radix Sort)", [&]() { sorter.radixSort(); }, pending);
}

void SortProfiler::radixSort(vector<int>& target) {
    profile("基数排序 (Radix Sort)", [&]() { sorter.radixSort(target); }, target);
}

// 运行全部排序算法（使用 pending）
void SortProfiler::runAll() {
    selectionSort();
    bubbleSort();
    insertionSort();
    shellSort();
    mergeSort();
    quickSort();
    heapSort();
    countingSort();
    bucketSort();
    radixSort();
}

// 运行全部排序算法（使用传入的 target）
void SortProfiler::runAll(vector<int>& target) {
    selectionSort(target);
    bubbleSort(target);
    insertionSort(target);
    shellSort(target);
    mergeSort(target);
    quickSort(target);
    heapSort(target);
    countingSort(target);
    bucketSort(target);
    radixSort(target);
}
