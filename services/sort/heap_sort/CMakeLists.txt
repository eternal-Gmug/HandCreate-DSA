project(heap_sort)

add_library(heap_sort_lib STATIC src/HeapSort.cpp)
target_link_libraries(heap_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(heap_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::HeapSort ALIAS heap_sort_lib)

add_executable(heap_sort src/main.cpp)
target_link_libraries(heap_sort PRIVATE HandCreate-DSA::HeapSort HandCreate-DSA::Common)
