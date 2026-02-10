#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include "Logger.h"

namespace HandCreateDSA {

    /// @brief 排序测试工具类.
    ///
    ///用于生成各种类型的测试数据（随机、有序、逆序等），
    ///并提供通用的测试运行和验证方法。
    class SortTester {
    public:
        enum class ArrayType {
            RANDOM,         ///< 完全随机
            SORTED,         ///< 已排序
            REVERSE_SORTED, ///< 逆序
            NEARLY_SORTED,  ///< 近似有序（少量乱序）
            FEW_UNIQUE      ///< 包含大量重复元素
        };

        /// @brief 生成指定的测试数组.
        /// @param size 数组大小.
        /// @param type 数组的数据分布类型.
        /// @param minVal 最小值 (针对随机类型).
        /// @param maxVal 最大值 (针对随机类型).
        /// @return 生成的 vector.
        static std::vector<int> generateArray(size_t size, ArrayType type, int minVal = 0, int maxVal = 10000);

        /// @brief 检查数组是否已有序.
        /// @param arr 待检查的数组.
        /// @return true 有序，false 无序.
        static bool isSorted(const std::vector<int>& arr);

        /// @brief 运行一个标准的排序测试用例.
        ///
        /// 生成随机数据，运行排序算法，验证结果，并记录性能日志。
        ///
        /// @param name 算法名称.
        /// @param sortFunc 排序函数对象 (void(std::vector<int>&)).
        /// @param dataSize 测试数据量.
        static void runProb(const std::string& name, std::function<void(std::vector<int>&)> sortFunc, int dataSize = 1000);

        /// @brief 供单元测试使用的简单验证函数.
        /// @param name 算法名称.
        /// @param sortFunc 排序函数.
        static void runUnitTests(const std::string& name, std::function<void(std::vector<int>&)> sortFunc);

        /// @brief 运行自定义数组的测试.
        ///
        /// 使用用户提供的数组进行测试，验证排序是否正确。
        /// output 到控制台。
        ///
        /// @param name 测试名称.
        /// @param sortFunc 排序函数.
        /// @param input 用户提供的测试数组 (按值传递，保证不修改原数组).
        static void runCustomTest(const std::string& name, std::function<void(std::vector<int>&)> sortFunc, std::vector<int> input);
    };

}
