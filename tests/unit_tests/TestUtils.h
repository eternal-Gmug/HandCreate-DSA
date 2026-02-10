#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "sort_profiler/SortTester.h"

// 保持接口兼容，内部转发调用共通的测试工具
static void run_test(const std::string& name, void (*sortFunc)(std::vector<int>&), size_t numElements = 20) {
    // 使用 std::function 包装函数指针
    HandCreateDSA::SortTester::runUnitTests(name, [sortFunc](std::vector<int>& arr){
        sortFunc(arr);
    }, numElements);
}

