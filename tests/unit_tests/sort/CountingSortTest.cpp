#include "TestUtils.h"
#include "sort.h"
#include "sort_profiler/SortTester.h"

int main() {
    // run_test("CountingSort", HandCreateDSA::Sort::countingSort);

    // Counting sort usually handles positive integers
    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::Sort::countingSort, customArray);

    return 0;
}
