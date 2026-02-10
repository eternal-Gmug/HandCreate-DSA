project(sorting_system)

add_executable(sorting_system src/main.cpp)

# 链接 common 库
target_link_libraries(sorting_system PRIVATE HandCreate-DSA::Common)
