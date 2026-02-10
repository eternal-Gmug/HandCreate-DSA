# HandCreate-DSA (手写数据结构与算法)

这是一个基于 C++ 的数据结构与算法实现项目，重点关注各种排序算法的实现、优化与性能分析。项目采用现代 C++ (C++17/20) 标准，并使用 CMake 进行构建管理。

## 项目目的

- **学习与实践**: 深入理解经典排序算法的内部机制和时间/空间复杂度。
- **性能分析**: 提供统一的 `SortProfiler` 和 `Logger` 工具，方便对不同算法在相同数据集下的性能进行对比。
- **代码规范**: 遵循 Google C++ Style Guide，注重代码的可读性与模块化设计。

## 项目架构

项目采用微服务式的目录结构（虽然是单体库），每个算法独立为一个子模块。

```
HandCreate-DSA/
├── common/              # 公共组件库
│   ├── include/
│   │   └── sort_profiler/  # 性能分析与日志工具
│   └── src/                # Logger 实现
├── services/            # 核心算法实现模块
│   ├── bubble_sort/     # 冒泡排序
│   ├── quick_sort/      # 快速排序 (含三路快排、双轴快排)
│   ├── merge_sort/      # 归并排序
│   ├── ...              # 其他排序算法 (Bucket, Counting, Heap, Insertion, Radix, Selection, Shell)
│   └── CMakeLists.txt   # 服务层构建配置
├── tests/               # 测试模块 (基于 GTest 或自定义测试框架)
│   ├── unit_tests/      # 单元测试
│   └── integration_tests/ # 集成测试
└── CMakeLists.txt       # 根项目构建配置
```

### 核心组件

- **Logger (common)**: 
  - 线程安全的单例日志记录器。
  - 支持将排序前后的数组状态自动记录到按日期分层的文件中。
  - output: `logs/YYYY_MM/DD/algorithm_timestamp.txt`

## 使用说明

### 前置要求

- CMake 3.10+
- 支持 C++17 的编译器 (MSVC, GCC, Clang)

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

编译完成后，可以在 `build/tests` 目录下找到测试可执行文件。

```bash
# 运行单元测试
./tests/unit_tests/unit_tests
```

## 新增子项目流程

如果想要添加一个新的算法（例如 `timsort`），请遵循以下步骤：

1.  **创建目录结构**:
    在 `services/` 下创建 `timsort` 目录：
    ```
    services/timsort/
    ├── CMakeLists.txt
    ├── include/
    │   └── TimSort.h
    └── src/
        └── TimSort.cpp
    ```

2.  **配置 CMakeLists.txt**:
    在 `services/timsort/CMakeLists.txt` 中添加：
    ```cmake
    project(timsort)

    add_library(timsort SHARED
        src/TimSort.cpp
    )

    target_include_directories(timsort PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    # 链接公共库
    target_link_libraries(timsort PUBLIC common)
    ```

3.  **注册服务**:
    修改 `services/CMakeLists.txt`，加入新目录：
    ```cmake
    add_subdirectory(timsort)
    ```

4.  **编写代码**:
    - 在 `.h` 文件中声明接口（参考 `BubbleSort.h` 的注释风格）。
    - 在 `.cpp` 文件中实现逻辑，并建议使用 `Logger` 记录开始和结束。

5.  **添加测试**:
    在 `tests/unit_tests/` 下创建 `TimSortTest.cpp` 并注册到 `tests/unit_tests/CMakeLists.txt`。

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
