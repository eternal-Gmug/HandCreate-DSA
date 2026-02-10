#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <mutex>

namespace HandCreateDSA {
    /// @brief 日志记录器类.
    ///
    /// 这是一个单例类，负责将应用程序的日志信息输出到控制台和文件。
    /// 包含了普通日志记录和排序结果记录的功能。
    /// 
    /// @warning 该类的方法是线程安全的 (Thread-safe)，内部使用了 mutex 锁。
    class Logger {
    private:
        std::string logPath; ///< 日志文件存储的基础路径.
        std::mutex logMutex; ///< 用于保证文件写入线程安全的互斥锁.
        
        /// @brief 私有构造函数.
        /// @param logDir 日志目录路径，默认为 "../logs".
        Logger(const std::string& logDir = "../logs");
        static Logger* instance;       ///< 单例实例指针.
        static std::mutex instanceMutex; ///< 用于获取单例实例的互斥锁.

        std::string getTimestamp();
        
    public:
        // Delete copy constructor and assignment operator
        /// @brief 禁止拷贝构造函数.
        Logger(const Logger&) = delete;
        /// @brief 禁止赋值操作符.
        Logger& operator=(const Logger&) = delete;

        /// @brief 获取日志记录器的单例实例.
        /// @param logDir 如果实例未创建，指定日志目录.
        /// @return Logger 实例的引用.
        static Logger& getInstance(const std::string& logDir = "../logs");
        
        /// @brief 记录普通日志消息.
        /// @param message 要记录的消息文本.
        void log(const std::string& message);

        /// @brief 记录排序算法的执行结果.
        ///
        /// 将排序前和排序后的数组以及耗时信息写入特定的日志文件。
        /// 文件路径结构为: logPath/YYYY_MM/DD/algorithm_timestamp.txt
        ///
        /// @param algorithmName 算法名称.
        /// @param before 排序前的数组 (const vector 引用).
        /// @param after 排序后的数组 (const vector 引用).
        /// @param elapsedMs 算法执行耗时 (毫秒).
        void logSortResult(const std::string& algorithmName, const std::vector<int>& before, const std::vector<int>& after, double elapsedMs);
        
        /// @brief 将整数向量转换为字符串表示.
        /// @param vec 要转换的向量.
        /// @return 形如 "[1, 2, 3]" 的字符串.
        std::string vecToString(const std::vector<int>& vec);
    };
}
