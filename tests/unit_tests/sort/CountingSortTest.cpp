#include "TestUtils.h"
#include "CountingSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("CountingSort", HandCreateDSA::countingSort);

    // Counting sort usually handles positive integers
    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::countingSort, customArray);

    return 0;
}
