cmake_minimum_required(VERSION 3.13)

project(GuruxDLMSServerExample
    DESCRIPTION "Gurux DLMS/COSEM Server Example"
    LANGUAGES C CXX
)

if (TARGET GuruxDLMS)
    set(GURUX_TARGET GuruxDLMS)
else()
    find_package(GuruxDLMS REQUIRED)
endif()

file(GLOB SERVER_EXAMPLE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(GuruxDLMSServerExample ${SERVER_EXAMPLE_SOURCES})

target_link_libraries(GuruxDLMSServerExample PRIVATE ${GURUX_TARGET} ws2_32)

target_include_directories(GuruxDLMSServerExample PRIVATE
    ${CMAKE_SOURCE_DIR}/development/include
    ./include
)

if (ENABLE_STRICT_MODE)
    if (MSVC)
        target_compile_options(GuruxDLMSServerExample PRIVATE /W4)
    else()
        target_compile_options(GuruxDLMSServerExample PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

set_target_properties(GuruxDLMSServerExample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
