#include "TestUtils.h"
#include "MergeSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("MergeSort", HandCreateDSA::mergeSort);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::mergeSort, customArray);

    return 0;
}
