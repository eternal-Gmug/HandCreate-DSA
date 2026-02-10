project(radix_sort)

add_library(radix_sort_lib STATIC src/RadixSort.cpp)
target_link_libraries(radix_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(radix_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::RadixSort ALIAS radix_sort_lib)

add_executable(radix_sort src/main.cpp)
target_link_libraries(radix_sort PRIVATE HandCreate-DSA::RadixSort HandCreate-DSA::Common)
