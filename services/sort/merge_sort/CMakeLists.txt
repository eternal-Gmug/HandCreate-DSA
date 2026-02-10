project(merge_sort)

add_library(merge_sort_lib STATIC src/MergeSort.cpp)
target_link_libraries(merge_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(merge_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::MergeSort ALIAS merge_sort_lib)

add_executable(merge_sort src/main.cpp)
target_link_libraries(merge_sort PRIVATE HandCreate-DSA::MergeSort HandCreate-DSA::Common)
