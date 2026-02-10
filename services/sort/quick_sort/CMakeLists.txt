project(quick_sort)

add_library(quick_sort_lib STATIC src/QuickSort.cpp)
target_link_libraries(quick_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(quick_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::QuickSort ALIAS quick_sort_lib)

add_executable(quick_sort src/main.cpp)
target_link_libraries(quick_sort PRIVATE HandCreate-DSA::QuickSort HandCreate-DSA::Common)
