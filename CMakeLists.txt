cmake_minimum_required(VERSION 3.15)
project(GuruxDLMS LANGUAGES C CXX)

# Google Test integration
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1 # Or a specific commit hash
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Источники библиотеки
file(GLOB_RECURSE GXDLMS_SOURCES development/src/*.cpp)
file(GLOB_RECURSE GXDLMS_HEADERS development/include/*.h)

add_library(gurux_dlms STATIC ${GXDLMS_SOURCES})
target_include_directories(gurux_dlms PUBLIC development/include)

# Client
file(GLOB_RECURSE GXDLMS_SOURCES GuruxDLMSClientExample/src/*.cpp)
add_executable(gurux_client ${GXDLMS_SOURCES})
target_link_libraries(gurux_client PRIVATE gurux_dlms)

# Listener
file(GLOB_RECURSE GXDLMS_SOURCES GuruxDLMSMeterListener/src/*.cpp)
add_executable(gurux_listener ${GXDLMS_SOURCES})
target_link_libraries(gurux_listener PRIVATE gurux_dlms)

# Listener
file(GLOB_RECURSE GXDLMS_SOURCES GuruxDLMSPushExample/src/*.cpp)
add_executable(gurux_push ${GXDLMS_SOURCES})
target_link_libraries(gurux_push PRIVATE gurux_dlms)

# Listener
file(GLOB_RECURSE GXDLMS_SOURCES GuruxDLMSServerExample/src/*.cpp)
add_executable(gurux_server ${GXDLMS_SOURCES})
target_link_libraries(gurux_server PRIVATE gurux_dlms)

enable_testing()

# DLMS Tests
# Force BUILD_TESTING to ON for this diagnosis
set(BUILD_TESTING ON CACHE BOOL "Enable testing" FORCE)
message(STATUS "BUILD_TESTING is ON")

if(BUILD_TESTING)
    message(STATUS "Inside BUILD_TESTING block")
    file(GLOB_RECURSE DLMS_TEST_SOURCES CONFIGURE_DEPENDS development/tests/*.cpp)
    message(STATUS "DLMS_TEST_SOURCES: ${DLMS_TEST_SOURCES}")
    if(DLMS_TEST_SOURCES)
        add_executable(dlms_tests ${DLMS_TEST_SOURCES})
        target_link_libraries(dlms_tests PRIVATE gurux_dlms gtest_main)
    else()
        message(WARNING "No test sources found for dlms_tests target.")
    endif()
    # Include GTest in CTest
    include(GoogleTest)
    gtest_discover_tests(dlms_tests)
endif()
