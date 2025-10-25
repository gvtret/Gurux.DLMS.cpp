cmake_minimum_required(VERSION 3.13)

project(gurux_tests
    VERSION 1.0
    DESCRIPTION "Test Suite"
    LANGUAGES C CXX
)

message(STATUS "Building unit tests")

# Download and setup GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test source files
set(TEST_SOURCES
    GXByteBufferTest.cpp
)

# Create test executable
add_executable(gurux_tests ${TEST_SOURCES})

# Link test executable with libraries
target_link_libraries(gurux_tests 
    PRIVATE 
    GuruxDLMS
    GTest::gtest_main
)

# Include directories for tests
target_include_directories(gurux_tests 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/development/include
    ${CMAKE_SOURCE_DIR}/tests
)

# Add test to CTest
# gtest_discover_tests(gurux_tests
#     EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml
# )

# Add custom test target for convenience
# add_custom_target(run_tests
#     COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
#     DEPENDS gurux_tests
#     COMMENT "Running unit tests..."
# )
