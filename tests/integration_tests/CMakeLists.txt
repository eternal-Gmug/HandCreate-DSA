add_executable(integration_test_runner IntegrationTestRunner.cpp)

# 设置默认的bin目录为构建目录下的bin
# 注意：在配置阶段，CMAKE_BINARY_DIR 是确定的
set(DEFAULT_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

# 添加一个CTest测试，默认运行所有apps
add_test(NAME IntegrationTests_All
    COMMAND integration_test_runner --bin-dir "${DEFAULT_BIN_DIR}"
)

# 示例：也可以添加特定的测试组
# add_test(NAME IntegrationTests_Simple
#     COMMAND integration_test_runner --bin-dir "${DEFAULT_BIN_DIR}" --include bubble selection insertion
# )
