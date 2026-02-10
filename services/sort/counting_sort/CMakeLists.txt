project(counting_sort)

add_library(counting_sort_lib STATIC src/CountingSort.cpp)
target_link_libraries(counting_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(counting_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::CountingSort ALIAS counting_sort_lib)

add_executable(counting_sort src/main.cpp)
target_link_libraries(counting_sort PRIVATE HandCreate-DSA::CountingSort HandCreate-DSA::Common)
