cmake_minimum_required(VERSION 3.13)

project(GuruxDLMSPushExample
    DESCRIPTION "Gurux DLMS/COSEM Push Example"
    LANGUAGES C CXX
)

if (TARGET GuruxDLMS)
    set(GURUX_TARGET GuruxDLMS)
else()
    find_package(GuruxDLMS REQUIRED)
endif()

file(GLOB PUSH_EXAMPLE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(GuruxDLMSPushExample ${PUSH_EXAMPLE_SOURCES})

if (WIN32)
    target_link_libraries(GuruxDLMSPushExample PRIVATE ${GURUX_TARGET} ws2_32)
else()
    target_link_libraries(GuruxDLMSPushExample PRIVATE ${GURUX_TARGET})
endif()

target_include_directories(GuruxDLMSPushExample PRIVATE
    ${CMAKE_SOURCE_DIR}/development/include
    ./include
)

if (ENABLE_STRICT_MODE)
    if (MSVC)
        target_compile_options(GuruxDLMSPushExample PRIVATE /W4)
    else()
        target_compile_options(GuruxDLMSPushExample PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

set_target_properties(GuruxDLMSPushExample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

print_target_size(GuruxDLMSPushExample)
