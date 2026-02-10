#include "TestUtils.h"
#include "sort.h"
#include "sort_profiler/SortTester.h"

int main() {
    // run_test("InsertionSort", HandCreateDSA::Sort::insertionSort);
    // run_test("InsertionSortOptimized", HandCreateDSA::Sort::insertionSortOptimized);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::Sort::insertionSort, customArray);

    return 0;
}
