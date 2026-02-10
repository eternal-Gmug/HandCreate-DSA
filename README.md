# HandCreate-DSA (手写数据结构与算法)

这是一个基于 C++ 的数据结构与算法实现项目，重点关注各种排序算法的实现、优化与性能分析。项目采用现代 C++ (C++17/20) 标准，并使用 CMake 进行构建管理。

## 项目目的

- **学习与实践**: 深入理解经典排序算法的内部机制和时间/空间复杂度。
- **性能分析**: 提供统一的 `SortProfiler` 和 `Logger` 工具，方便对不同算法在相同数据集下的性能进行对比。
- **代码规范**: 遵循 Dxygen，注重代码的可读性与模块化设计。

## 项目架构

项目采用微服务式的目录结构（虽然是单体库），每个算法独立为一个子模块。

```
HandCreate-DSA/
├── common/              # 公共组件库
│   ├── include/
│   │   └── sort_profiler/  # 性能分析与日志工具 (SortTester, Logger)
│   └── src/                # 公共组件实现
├── services/            # 核心算法实现模块
│   └── sort/            # 排序服务模块
│       ├── include/     # 统一头文件 (sort.h)
│       └── src/         # 排序算法实现 (sort.cpp)
├── tests/               # 测试模块
│   ├── unit_tests/      # 单元测试 (针对各个算法的独立测试)
│   └── integration_tests/ # 集成测试 (Unified TestSorts)
└── CMakeLists.txt       # 根项目构建配置
```

### 核心组件

- **Logger (common)**: 
  - 线程安全的单例日志记录器。
  - 支持将排序前后的数组状态自动记录到按日期分层的文件中。
  - Path structure: `build/logs/YYYY/MM/DD/algorithmname_yyyy_mm_dd_hh_mm_ss.txt`
  - Output format: 包含时间、数据量、排序前/后状态、精确耗时(ms)。

## 使用说明

### 前置要求

- CMake 3.10+
- 支持 C++17 的编译器 (MSVC, GCC, Clang)
- Windows (处理中文日志输出时建议配套)

### 构建项目

```bash
# 1. 创建构建目录
mkdir build
cd build

# 2. 生成构建文件
cmake ..

# 3. 编译
cmake --build . 
```

### 运行测试

编译完成后，可以在 `build/bin` 目录下找到测试可执行文件。

```bash
# 运行所有测试 (通过 CTest)
ctest -V

# 运行集成测试 (包含所有算法)
./bin/integration_tests

# 运行特定算法的单元测试
./bin/test_BubbleSort
./bin/test_QuickSort
# ...
```

## 新增排序算法流程

本项目已将所有排序算法合并至统一的服务模块中。如果想要添加一个新的算法（例如 `timsort`），请遵循以下步骤：

1.  **添加接口**:
    在 `services/sort/include/sort.h` 的 `HandCreateDSA::Sort` 类中添加静态方法声明：
    ```cpp
    /// @brief TimSort 算法实现.
    /// ...
    static void timSort(std::vector<int>& target);
    ```

2.  **实现逻辑**:
    在 `services/sort/src/sort.cpp` 中实现具体逻辑。建议在开始和结束调用 Logger：
    ```cpp
    void Sort::timSort(std::vector<int>& target) {
        Logger::getInstance().log("TimSort started.");
        // 实现代码...
        Logger::getInstance().log("TimSort finished.");
    }
    ```

3.  **添加测试**:
    - 在 `tests/unit_tests/sort/` 下创建 `TimSortTest.cpp`。
    - 使用 `run_test` 宏或 `SortTester::runCustomTest` 进行测试。
    - 在 `tests/unit_tests/CMakeLists.txt` 中注册新的测试：
      ```cmake
      add_sort_test(TimSort HandCreate-DSA::Sort)
      ```
    - 在 `tests/integration_tests/TestSorts.cpp` 中加入集成测试调用。

## 代码注释规范

本项目严格遵循详细的中文注释规范：

- **头文件 (.h)**: 使用 Doxygen 风格 (`///`) 注释，包括 
    `@brief`: 简短说明（第一行）。现在的 Doxygen 配置通常允许省略这个标签，直接把第一行当作简述，但写上更规范。

    `@details`: 详细说明。通常不需要显式写这个标签，@brief 之后空一行写的内容默认就是 details。

    `@param`: 参数说明。格式：@param name description。可以加 [in], [out] 标记方向，如 @param[out] result。

    `@return`: 返回值说明。

    `@throw` (或 @exception): 可能抛出的异常。

    `@see` (或 @sa): 参见，用于链接到其他函数。

    `@note`: 提示/注意点。

    `@warning`: 警告，通常用于标记非线程安全或高风险操作。

- **源文件 (.cpp)**: 在关键算法步骤前添加实现细节注释 (`// [步骤名称]`)，解释"为什么这么做"而不仅仅是"做了什么"。
