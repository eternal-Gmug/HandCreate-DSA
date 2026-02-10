project(selection_sort)

add_library(selection_sort_lib STATIC src/SelectionSort.cpp)
target_link_libraries(selection_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(selection_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::SelectionSort ALIAS selection_sort_lib)

add_executable(selection_sort src/main.cpp)
target_link_libraries(selection_sort PRIVATE HandCreate-DSA::SelectionSort HandCreate-DSA::Common)
