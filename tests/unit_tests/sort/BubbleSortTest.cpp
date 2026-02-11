#include "TestUtils.h"
#include "sort.h"
#include "sort_profiler/SortTester.h"

int main() {
    // 1. 运行自动化的标准单元测试，自动随机生成数组
    // run_test("loggerForntName", HandCreateDSA::Sort::bubbleSort, 1000);

    // 2. 运行自定义数组测试
    std::vector<int> myCustomArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", [](std::vector<int>& arr,int flag) {
        HandCreateDSA::Sort::bubbleSort(arr, flag);
    }, myCustomArray, 1);

    return 0;
}
