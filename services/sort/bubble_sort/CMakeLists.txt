project(bubble_sort)

add_library(bubble_sort_lib STATIC src/BubbleSort.cpp)
target_link_libraries(bubble_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(bubble_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::BubbleSort ALIAS bubble_sort_lib)

add_executable(bubble_sort src/main.cpp)
target_link_libraries(bubble_sort PRIVATE HandCreate-DSA::BubbleSort HandCreate-DSA::Common)
