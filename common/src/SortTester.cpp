#include "sort_profiler/SortTester.h"
#include <chrono>

namespace HandCreateDSA {

    std::vector<int> SortTester::generateArray(size_t size, ArrayType type, int minVal, int maxVal) {
        std::vector<int> arr(size);
        std::mt19937 gen(std::random_device{}());

        switch (type) {
        case ArrayType::SORTED:
            for (size_t i = 0; i < size; ++i) arr[i] = static_cast<int>(i);
            break;

        case ArrayType::REVERSE_SORTED:
            for (size_t i = 0; i < size; ++i) arr[i] = static_cast<int>(size - i);
            break;

        case ArrayType::NEARLY_SORTED:
            for (size_t i = 0; i < size; ++i) arr[i] = static_cast<int>(i);
            {
                std::uniform_int_distribution<> dis(0, static_cast<int>(size) - 1);
                // 交换约 5% 的元素
                int swaps = std::max(1, static_cast<int>(size * 0.05));
                for (int i = 0; i < swaps; ++i) {
                    std::swap(arr[dis(gen)], arr[dis(gen)]);
                }
            }
            break;

        case ArrayType::FEW_UNIQUE:
            {
                std::uniform_int_distribution<> dis(minVal, std::min(minVal + 10, maxVal));
                for (size_t i = 0; i < size; ++i) {
                    arr[i] = dis(gen);
                }
            }
            break;

        case ArrayType::RANDOM:
        default:
            {
                std::uniform_int_distribution<> dis(minVal, maxVal);
                for (size_t i = 0; i < size; ++i) {
                    arr[i] = dis(gen);
                }
            }
            break;
        }

        return arr;
    }

    bool SortTester::isSorted(const std::vector<int>& arr) {
        for (size_t i = 0; i < arr.size() - 1; ++i) {
            if (arr[i] > arr[i + 1]) return false;
        }
        return true;
    }

    void SortTester::runProb(const std::string& name, std::function<void(std::vector<int>&)> sortFunc, int dataSize) {
        std::cout << "Running performance test for: " << name << " with size " << dataSize << std::endl;
        
        auto arr = generateArray(dataSize, ArrayType::RANDOM);
        auto before = arr; // Copy for logging if small enough, or verification

        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        if (!isSorted(arr)) {
            std::cerr << "ERROR: " << name << " failed to sort the array!" << std::endl;
            Logger::getInstance().log("ERROR: " + name + " failed comparison check.");
        } else {
            Logger::getInstance().logSortResult(name, before, arr, elapsed.count());
        }
    }

    void SortTester::runUnitTests(const std::string& name, std::function<void(std::vector<int>&)> sortFunc, size_t numElements) {
        Logger::getInstance().log("Unit Tests started for: " + name);
        
        // 1. Basic Random
        {
            auto arr = generateArray(numElements, ArrayType::RANDOM, -50, 50);
            auto before = arr;

            auto start = std::chrono::high_resolution_clock::now();
            sortFunc(arr);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;

            if (!isSorted(arr)) {
                std::cerr << name << ": Failed random small test." << std::endl;
                exit(1);
            }
            Logger::getInstance().logSortResult(name + "_UnitTest_Random", before, arr, elapsed.count());
        }
        
        // 2. Empty
        {
            std::vector<int> arr;
            sortFunc(arr);
            if (!arr.empty()) {
                std::cerr << name << ": Failed empty array test." << std::endl;
                exit(1);
            }
        }

        // 3. Single Element
        {
            std::vector<int> arr = { 42 };
            sortFunc(arr);
            if (arr.size() != 1 || arr[0] != 42) {
                std::cerr << name << ": Failed single element test." << std::endl;
                exit(1);
            }
        }
        
        // 4. Sorted
        {
            auto arr = generateArray(20, ArrayType::SORTED);
            sortFunc(arr);
            if (!isSorted(arr)) {
                std::cerr << name << ": Failed already sorted test." << std::endl;
                exit(1);
            }
        }

         // 5. Reverse Sorted
        {
            auto arr = generateArray(20, ArrayType::REVERSE_SORTED);
            sortFunc(arr);
            if (!isSorted(arr)) {
                std::cerr << name << ": Failed reverse sorted test." << std::endl;
                exit(1);
            }
        }

        std::cout << name << " passed all unit tests." << std::endl;
        Logger::getInstance().log("Unit Tests passed for: " + name);
    }

    void SortTester::runCustomTest(const std::string& name, std::function<void(std::vector<int>&, int)> sortFunc, std::vector<int> input,int flag) {
        Logger::getInstance().log("Custom Test started: " + name);
        std::vector<int> originalForMatch = input;
        std::vector<int> originalForLog = input;
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(input,flag);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        if (!isSorted(input)) {
            std::cerr << "FAIL: " << name << " - Array is not sorted!" << std::endl;
            std::cerr << "Original: " << Logger::getInstance().vecToString(originalForMatch) << std::endl;
            std::cerr << "Result:   " << Logger::getInstance().vecToString(input) << std::endl;
            exit(1);
        } else {
             // 简单的长度和元素守恒检查（通过比较排序后的原始副本）
            std::sort(originalForMatch.begin(), originalForMatch.end());
            bool match = (originalForMatch == input);
            if (!match) {
                 std::cerr << "FAIL: " << name << " - Array is sorted but elements do not match original!" << std::endl;
                 Logger::getInstance().log("FAIL: " + name + " - Element mismatch.");
                 exit(1);
            }
            std::cout << "PASS: " << name << " (Custom Input)" << std::endl;
            Logger::getInstance().log("Custom Test passed: " + name);
            Logger::getInstance().logSortResult(name + "_Custom", originalForLog, input, elapsed.count());
        }
    }

}
