#include "TestUtils.h"
#include "BubbleSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    // 1. 运行自动化的标准单元测试
    run_test("BubbleSort", HandCreateDSA::bubbleSort);

    // 2. 运行自定义数组测试
    // 您可以在这里添加任何想要测试的特定数组
    std::vector<int> myCustomArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::bubbleSort, myCustomArray);

    return 0;
}
