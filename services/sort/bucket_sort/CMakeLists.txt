project(bucket_sort)

add_library(bucket_sort_lib STATIC src/BucketSort.cpp)
target_link_libraries(bucket_sort_lib PRIVATE HandCreate-DSA::Common)

target_include_directories(bucket_sort_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(HandCreate-DSA::BucketSort ALIAS bucket_sort_lib)

add_executable(bucket_sort src/main.cpp)
target_link_libraries(bucket_sort PRIVATE HandCreate-DSA::BucketSort HandCreate-DSA::Common)
