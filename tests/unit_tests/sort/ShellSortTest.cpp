#include "TestUtils.h"
#include "ShellSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("ShellSort", HandCreateDSA::shellSort);

    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::shellSort, customArray);

    return 0;
}
