cmake_minimum_required(VERSION 3.13)

project(GuruxDLMSClientExample
    DESCRIPTION "Gurux DLMS/COSEM Client Example"
    LANGUAGES C CXX
)

# Locate the library (use in-tree build or system)
if (TARGET GuruxDLMS)
    set(GURUX_TARGET GuruxDLMS)
else()
    find_package(GuruxDLMS REQUIRED)
endif()

# Gather sources
file(GLOB CLIENT_EXAMPLE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(GuruxDLMSClientExample ${CLIENT_EXAMPLE_SOURCES})

# Link against the DLMS library
target_link_libraries(GuruxDLMSClientExample PRIVATE ${GURUX_TARGET} ws2_32)

# Include library headers
target_include_directories(GuruxDLMSClientExample PRIVATE
    ${CMAKE_SOURCE_DIR}/development/include
    ./include
)

# Compiler options (inherit strict mode)
if (ENABLE_STRICT_MODE)
    if (MSVC)
        target_compile_options(GuruxDLMSClientExample PRIVATE /W4)
    else()
        target_compile_options(GuruxDLMSClientExample PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

set_target_properties(GuruxDLMSClientExample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
