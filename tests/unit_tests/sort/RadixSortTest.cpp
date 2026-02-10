#include "TestUtils.h"
#include "RadixSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("RadixSort", HandCreateDSA::radixSort);

    // Radix sort usually handles positive integers
    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::radixSort, customArray);

    return 0;
}
