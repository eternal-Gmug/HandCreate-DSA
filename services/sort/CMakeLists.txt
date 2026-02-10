project(sort_service)

add_library(sort_lib STATIC
    src/sort.cpp
)

target_include_directories(sort_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sort_lib PRIVATE HandCreate-DSA::Common)
add_library(HandCreate-DSA::Sort ALIAS sort_lib)
