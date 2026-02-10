project(common)
#定义库目标
add_library(common_lib STATIC
    src/Logger.cpp
    src/SortTester.cpp
)
# 公开 include 目录给使用者
target_include_directories(common_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/sort_profiler>
    $<INSTALL_INTERFACE:include>
)
#定义库别名用于其他引用者区分内部库外部库
add_library(HandCreate-DSA::Common ALIAS common_lib)

# 链接其他第三方库（比如 fmt）
#target_link_libraries(common_lib PRIVATE fmt::fmt)