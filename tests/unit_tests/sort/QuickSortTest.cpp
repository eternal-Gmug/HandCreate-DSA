#include "TestUtils.h"
#include "sort.h"
#include "sort_profiler/SortTester.h"

int main() {
    // run_test("QuickSort", HandCreateDSA::Sort::quickSort);
    // run_test("QuickSort3Way", HandCreateDSA::Sort::quickSort3Way);
    // run_test("DualPivotQuickSort", HandCreateDSA::Sort::dualPivotQuickSort);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::Sort::quickSort, customArray);

    return 0;
}
