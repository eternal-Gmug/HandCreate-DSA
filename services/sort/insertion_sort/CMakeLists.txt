project(insertion_sort)

add_library(insertion_sort_lib STATIC src/InsertionSort.cpp)
target_link_libraries(insertion_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(insertion_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::InsertionSort ALIAS insertion_sort_lib)

add_executable(insertion_sort src/main.cpp)
target_link_libraries(insertion_sort PRIVATE HandCreate-DSA::InsertionSort HandCreate-DSA::Common)
