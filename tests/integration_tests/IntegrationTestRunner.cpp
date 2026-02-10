#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;

struct Config {
    fs::path binDir;
    std::vector<std::string> includes;
    std::vector<std::string> excludes;
};

// Simple argument parser
Config parseArgs(int argc, char* argv[]) {
    Config config;
    // Default to current directory if not specified, 
    // but usually CTest runs in build/tests/integration_tests, executables are in build/bin
    // We expect the caller to provide --bin-dir
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--bin-dir" && i + 1 < argc) {
            config.binDir = argv[++i];
        } else if (arg == "--include") {
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                config.includes.push_back(argv[++i]);
            }
        } else if (arg == "--exclude") {
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                config.excludes.push_back(argv[++i]);
            }
        }
    }
    return config;
}

bool shouldRun(const std::string& filename, const Config& config) {
    // Must end with _app.exe (on Windows) or _app
    // We can just check for "_app" substring to be safe and cross-platform friendly for logic
    if (filename.find("_app") == std::string::npos) {
        return false;
    }
    
    // Check excludes first
    for (const auto& excl : config.excludes) {
        if (filename.find(excl) != std::string::npos) {
            return false;
        }
    }
    
    // If includes specified, must match at least one
    if (!config.includes.empty()) {
        bool found = false;
        for (const auto& incl : config.includes) {
            if (filename.find(incl) != std::string::npos) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    
    return true;
}

int main(int argc, char* argv[]) {
    Config config = parseArgs(argc, argv);
    
    if (config.binDir.empty() || !fs::exists(config.binDir)) {
        std::cerr << "Error: valid --bin-dir is required." << std::endl;
        return 1;
    }

    std::cout << "Scanning directory: " << config.binDir << std::endl;

    std::vector<fs::path> appsToRun;
    for (const auto& entry : fs::directory_iterator(config.binDir)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            // Simple check for exe extension on Windows or no extension on *nix + executable bit (omitted for simplicity)
            // Combined with _app helper
            if (filename.find("_app") != std::string::npos) {
                 if (shouldRun(filename, config)) {
                     appsToRun.push_back(entry.path());
                 }
            }
        }
    }

    if (appsToRun.empty()) {
        std::cout << "No matching applications found." << std::endl;
        // Depending on requirements, maybe valid to find nothing if strictly filtered?
        // But usually we want to know if tests aren't running.
        return 0;
    }

    std::cout << "Found " << appsToRun.size() << " apps to run." << std::endl;
    
    int failures = 0;
    for (const auto& appPath : appsToRun) {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Running: " << appPath.filename() << std::endl;
        
        std::string cmd = appPath.string();
        
        // Use std::system to run. Output goes to stdout/stderr automatically.
        int ret = std::system(cmd.c_str());
        
        if (ret == 0) {
            std::cout << "PASS" << std::endl;
        } else {
            std::cout << "FAIL (Code: " << ret << ")" << std::endl;
            failures++;
        }
    }
    
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Summary: " << (appsToRun.size() - failures) << " Passed, " << failures << " Failed." << std::endl;
    
    return failures > 0 ? 1 : 0;
}
