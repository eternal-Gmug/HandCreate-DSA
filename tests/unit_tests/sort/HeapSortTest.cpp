#include "TestUtils.h"
#include "HeapSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("HeapSort", HandCreateDSA::heapSort);
    
    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::heapSort, customArray);

    return 0;
}
