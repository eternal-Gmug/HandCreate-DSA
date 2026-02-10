#include "TestUtils.h"
#include "QuickSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("QuickSort", HandCreateDSA::quickSort);
    run_test("QuickSort3Way", HandCreateDSA::quickSort3Way);
    run_test("DualPivotQuickSort", HandCreateDSA::dualPivotQuickSort);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::quickSort, customArray);

    return 0;
}
