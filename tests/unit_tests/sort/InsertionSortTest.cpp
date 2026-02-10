#include "TestUtils.h"
#include "InsertionSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("InsertionSort", HandCreateDSA::insertionSort);
    run_test("InsertionSortOptimized", HandCreateDSA::insertionSortOptimized);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::insertionSort, customArray);

    return 0;
}
