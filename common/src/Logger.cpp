#include "sort_profiler/Logger.h"
#include <algorithm> // for transform, replace

namespace HandCreateDSA {

    Logger* Logger::instance = nullptr;
    std::mutex Logger::instanceMutex;

    Logger::Logger(const std::string& logDir) {
        // [路径初始化]
        // 检查路径是否为绝对路径，如果不是则基于当前工作目录构建
        std::filesystem::path path(logDir);
        if (path.is_absolute()) {
             logPath = path.string();
        } else {
             logPath = (std::filesystem::current_path() / path).string();
        }

        // [目录创建]
        // 如果目录不存在，递归创建所有必要的父目录
        if (!std::filesystem::exists(logPath)) {
            std::filesystem::create_directories(logPath);
        }
    }

    Logger& Logger::getInstance(const std::string& logDir) {
        // [单例模式]
        // 使用双重检查锁定 (Double-checked locking) 确保线程安全的实例创建
        std::lock_guard<std::mutex> lock(instanceMutex);
        if (instance == nullptr) {
            instance = new Logger(logDir);
        }
        return *instance;
    }

    std::string Logger::getTimestamp() {
        // [时间获取]
        // 获取系统当前时间并格式化为 YYYY-MM-DD HH:MM:SS
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;
        localtime_s(&localTime, &t);
        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    std::string Logger::vecToString(const std::vector<int>& vec) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < vec.size(); i++) {
            oss << vec[i];
            if (i < vec.size() - 1) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    void Logger::log(const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);
        std::string filename = logPath + "/app_log.txt";
        std::ofstream logFile(filename, std::ios::app);
        
        std::string timestamp = getTimestamp();
        std::string formattedMsg = "[" + timestamp + "] " + message;

        if (logFile.is_open()) {
            logFile << formattedMsg << std::endl;
        }
        // 同时输出到控制台
        std::cout << formattedMsg << std::endl;
    }

    void Logger::logSortResult(const std::string& algorithmName, const std::vector<int>& before, const std::vector<int>& after, double elapsedMs) {
        std::lock_guard<std::mutex> lock(logMutex);
        
        // [时间处理]
        // 获取当前时间用于生成文件名
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        
        // 使用 localtime 将时间转换为本地时间结构
        // 这里的操作是在锁内进行的，所以是安全的
        std::tm* localTimePtr = std::localtime(&t);
        std::tm localTime = *localTimePtr;

        // [目录结构]
        // 按年月/日分层存储日志
        std::ostringstream monthSS;
        monthSS << std::put_time(&localTime, "%Y_%m");
        std::string monthDir = monthSS.str();

        std::ostringstream daySS;
        daySS << std::put_time(&localTime, "%d");
        std::string dayDir = daySS.str();

        // [文件名生成]
        // 规范化算法名称（转小写，空格换下划线）
        std::string safeName = algorithmName;
        std::transform(safeName.begin(), safeName.end(), safeName.begin(), 
            [](unsigned char c){ return std::tolower(c); });
        std::replace(safeName.begin(), safeName.end(), ' ', '_');

        std::ostringstream fileSS;
        fileSS << safeName << "_" << std::put_time(&localTime, "%Y_%m_%d_%H%M%S") << ".txt";
        std::string logFileName = fileSS.str();

        // [路径构建]
        // 完整路径: logPath / Month / Day / Timestamp.txt
        std::filesystem::path basePath(logPath);
        std::filesystem::path targetDir = basePath / monthDir / dayDir;

        if (!std::filesystem::exists(targetDir)) {
            std::filesystem::create_directories(targetDir);
        }

        std::filesystem::path fullPath = targetDir / logFileName;
        // 规范化路径，移除 "." 和 ".."
        fullPath = fullPath.lexically_normal();
        std::string filename = fullPath.string();

        // [文件写入]
        std::ofstream logFile(filename, std::ios::out); 
                                                        
        if (!logFile.is_open()) {
            std::cerr << "无法打开日志文件: " << filename << std::endl;
            return;
        }

        logFile << "========================================" << std::endl;
        logFile << "时间: " << getTimestamp() << std::endl;
        logFile << "算法: " << algorithmName << std::endl;
        logFile << "数据量: " << before.size() << " 个元素" << std::endl;
        // 注意：如果数据量非常大，这里打印所有数据可能会导致文件过大
        logFile << "排序前: " << vecToString(before) << std::endl;
        logFile << "排序后: " << vecToString(after) << std::endl;
        logFile << "耗时: " << std::fixed << std::setprecision(4) << elapsedMs << " ms" << std::endl;
        logFile << "========================================" << std::endl;
        logFile << std::endl;
        logFile.close();

        std::cout << "[SortProfiler] " << algorithmName
             << " 完成, 耗时 " << std::fixed << std::setprecision(4) << elapsedMs << " ms"
             << " (已记录到 " << filename << ")" << std::endl;
    }
}

