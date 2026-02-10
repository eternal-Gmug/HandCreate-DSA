project(shell_sort)

add_library(shell_sort_lib STATIC src/ShellSort.cpp)
target_link_libraries(shell_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(shell_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::ShellSort ALIAS shell_sort_lib)

add_executable(shell_sort src/main.cpp)
target_link_libraries(shell_sort PRIVATE HandCreate-DSA::ShellSort HandCreate-DSA::Common)
