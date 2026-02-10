#include "TestUtils.h"
#include "BucketSort.h"
#include "sort_profiler/SortTester.h"

int main() {
    run_test("BucketSort", HandCreateDSA::bucketSort);

    // Bucket sort usually handles positive integers
    std::vector<int> customArray = { 99, 10, 5, 100, 2, 8, 1 };
    HandCreateDSA::SortTester::runCustomTest("My Custom Case", HandCreateDSA::bucketSort, customArray);

    return 0;
}
