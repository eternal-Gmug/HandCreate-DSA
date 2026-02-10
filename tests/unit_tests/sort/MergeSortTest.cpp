#include "TestUtils.h"
#include "sort.h"
#include "sort_profiler/SortTester.h"

int main() {
    // run_test("MergeSort", HandCreateDSA::Sort::mergeSort);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::Sort::mergeSort, customArray);

    return 0;
}
