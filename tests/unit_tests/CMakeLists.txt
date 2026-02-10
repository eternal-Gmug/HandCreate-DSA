
macro(add_sort_test name lib)
    # 源文件现在位于 sort 子目录中
    add_executable(test_${name} sort/${name}Test.cpp)
    # 链接 common 库以使用 SortTester
    target_link_libraries(test_${name} PRIVATE ${lib} HandCreate-DSA::Common)
    # 添加当前目录到包含路径，以便能找到 TestUtils.h
    target_include_directories(test_${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME ${name} COMMAND test_${name})
endmacro()

add_sort_test(BubbleSort      HandCreate-DSA::Sort)
add_sort_test(SelectionSort   HandCreate-DSA::Sort)
add_sort_test(InsertionSort   HandCreate-DSA::Sort)
add_sort_test(ShellSort       HandCreate-DSA::Sort)
add_sort_test(MergeSort       HandCreate-DSA::Sort)
add_sort_test(QuickSort       HandCreate-DSA::Sort)
add_sort_test(HeapSort        HandCreate-DSA::Sort)
add_sort_test(CountingSort    HandCreate-DSA::Sort)
add_sort_test(BucketSort      HandCreate-DSA::Sort)
add_sort_test(RadixSort       HandCreate-DSA::Sort)
