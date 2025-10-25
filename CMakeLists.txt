cmake_minimum_required(VERSION 3.13)

project(
  GuruxDLMS
  VERSION 1.0
  DESCRIPTION "Gurux DLMS/COSEM C++ Library"
  LANGUAGES C CXX)

function(print_target_size target)
  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -DTARGET_PATH=$<TARGET_FILE:${target}> -P
            ${CMAKE_SOURCE_DIR}/print_size.cmake
    COMMENT "Calculating size of built binary")
endfunction()

# ----------------------------------------------------------
# Universal options
# ----------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)
option(BUILD_EXAMPLES "Build example applications" ON)
option(ENABLE_STRICT_MODE "Enable strict compiler warnings" ON)
option(ENABLE_EMBEDDED "Enable embedded platform detection" ON)
option(BUILD_TESTS "Build unit tests" ON)

# Force CMake to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Language standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
message(STATUS ${build_type})
if(build_type STREQUAL debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gdwarf-2 -O0 -rdynamic")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-2 -O0 -rdynamic")
  add_definitions(-DDEBUG)
  add_definitions(-U_FORTIFY_SOURCE)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/development/include)

if(MINGW)
  set(IS_MINGW TRUE)
elseif(MSVC)
  set(IS_MSVC TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Unix")
  set(IS_LINUX TRUE)
endif()

# ----------------------------------------------------------
# Detect embedded environments (mbed / FreeRTOS / Buildroot / Poky)
# ----------------------------------------------------------
set(EMBEDDED_PLATFORM "none")

if(ENABLE_EMBEDDED)
  # mbed detection
  if(DEFINED ENV{MBED_OS_PATH} OR EXISTS "${CMAKE_SOURCE_DIR}/mbed-os")
    set(EMBEDDED_PLATFORM "mbed")
    message(STATUS "[Detected] mbed OS environment")

    # FreeRTOS detection
  elseif(DEFINED ENV{FREERTOS_PATH} OR EXISTS "${CMAKE_SOURCE_DIR}/FreeRTOS")
    set(EMBEDDED_PLATFORM "freertos")
    message(STATUS "[Detected] FreeRTOS environment")

    # Buildroot / Poky toolchains
  elseif(DEFINED ENV{BR2_TOOLCHAIN_EXTERNAL_PATH} OR DEFINED
                                                     ENV{OECORE_TARGET_SYSROOT})
    set(EMBEDDED_PLATFORM "buildroot_poky")
    message(STATUS "[Detected] Buildroot / Poky toolchain")
  endif()
endif()

# ----------------------------------------------------------
# Cross-compilation setup
# ----------------------------------------------------------
if(EMBEDDED_PLATFORM STREQUAL "mbed"
   OR EMBEDDED_PLATFORM STREQUAL "freertos"
   OR EMBEDDED_PLATFORM STREQUAL "buildroot_poky")
  if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compilation mode active")
  else()
    # Detect ARM toolchains heuristically
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_NAME MATCHES
                                               ".*ARM.*")
      set(CMAKE_SYSTEM_NAME Generic)
      set(CMAKE_SYSTEM_PROCESSOR arm)
    endif()
  endif()

  # Common ARM flags
  set(ARM_FLAGS
      "-mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti"
  )
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARM_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARM_FLAGS}")

  # Linker optimizations for embedded
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")

  message(STATUS "Configured embedded/ARM toolchain flags.")
endif()

# ----------------------------------------------------------
# Collect source files
# ----------------------------------------------------------
file(GLOB_RECURSE DLMS_SOURCES
     "${CMAKE_CURRENT_SOURCE_DIR}/development/src/*.cpp")

add_library(GuruxDLMS ${DLMS_SOURCES})

print_target_size(GuruxDLMS)

# Link Winsock on Windows
if(WIN32)
  target_link_libraries(GuruxDLMS PRIVATE ws2_32)
endif()

target_include_directories(
  GuruxDLMS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/development/include)

# -------------------------------------------------------------------
# Compiler and platform specific options
# -------------------------------------------------------------------

if(IS_MSVC)
  message(STATUS "Configuring for MSVC")
  target_compile_definitions(
    GuruxDLMS PRIVATE _CRT_SECURE_NO_WARNINGS WIN32_LEAN_AND_MEAN NOMINMAX
                      NOUSER)
  target_compile_options(GuruxDLMS PRIVATE /W4 /EHsc)

elseif(IS_MINGW)
  message(STATUS "Configuring for MinGW")
  target_compile_definitions(
    GuruxDLMS PRIVATE _CRT_SECURE_NO_WARNINGS WIN32_LEAN_AND_MEAN NOMINMAX
                      NOUSER __USE_MINGW_ANSI_STDIO)
  # MinGW-specific fixes for C++11 compliance and runtime behavior
  target_compile_options(GuruxDLMS PRIVATE -Wall -Wextra -Wpedantic
                                           -Wno-unknown-pragmas -fpermissive)

elseif(IS_LINUX)
  message(STATUS "Configuring for Linux/Unix")
  target_compile_options(GuruxDLMS PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ----------------------------------------------------------
# Compiler flags
# ----------------------------------------------------------
if(ENABLE_STRICT_MODE)
  if(MSVC)
    target_compile_options(GuruxDLMS PRIVATE /W4 /permissive-)
  else()
    target_compile_options(GuruxDLMS PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
  endif()
endif()

# ----------------------------------------------------------
# Build type settings
# ----------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "Choose the build type: Debug or Release" FORCE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -flto")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -flto")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")

# ----------------------------------------------------------
# Example targets (optional)
# ----------------------------------------------------------
if(BUILD_EXAMPLES)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/GuruxDLMSClientExample/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GuruxDLMSClientExample)
  endif()
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/GuruxDLMSServerExample/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GuruxDLMSServerExample)
  endif()
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/GuruxDLMSPushExample/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GuruxDLMSPushExample)
  endif()
endif()

# ----------------------------------------------------------
# Installation rules
# ----------------------------------------------------------
install(
  TARGETS GuruxDLMS
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/development/include/
        DESTINATION include)

if(BUILD_TESTS)
  include(CTest)
	enable_testing()
  add_subdirectory(tests)
endif()
# ----------------------------------------------------------
# Summary
# ----------------------------------------------------------
message(STATUS "------------------------------------------------------")
message(STATUS " Gurux DLMS/COSEM Build Configuration Summary")
message(STATUS " Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS " Shared libs: ${BUILD_SHARED_LIBS}")
message(STATUS " Strict mode: ${ENABLE_STRICT_MODE}")
message(STATUS " Embedded platform: ${EMBEDDED_PLATFORM}")
message(STATUS " Examples: ${BUILD_EXAMPLES}")
message(STATUS " Compile commands: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message(STATUS " Build tests: ${BUILD_TESTS}")
message(STATUS "------------------------------------------------------")
