cmake_minimum_required(VERSION 3.10)
project(HandCreate-DSA VERSION 1.0)

# 设置全局编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 解决 Windows 控制台中文乱码：告诉编译器源文件和执行字符集均为 UTF-8
add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8;-fexec-charset=UTF-8>")
#统一输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置第三方库路径
set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)

# 添加子目录
add_subdirectory(common)
add_subdirectory(services/sorting_system)
# add_subdirectory(external) # Uncomment when external libs are added
# add_subdirectory(tests)    # Uncomment when tests are added
