#include "TestUtils.h"
#include "SelectionSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("SelectionSort", HandCreateDSA::selectionSort);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::selectionSort, customArray);

    return 0;
}
