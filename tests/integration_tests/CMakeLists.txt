project(integration_tests)

add_executable(integration_tests TestSorts.cpp)

target_link_libraries(integration_tests PRIVATE 
    HandCreate-DSA::Sort
    HandCreate-DSA::Common
)

add_test(NAME IntegrationTests COMMAND integration_tests)
