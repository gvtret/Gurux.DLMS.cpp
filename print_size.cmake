if(NOT DEFINED TARGET_PATH)
	message(FATAL_ERROR "TARGET_PATH not defined")
endif()

file(SIZE "${TARGET_PATH}" size)
math(EXPR size_kb "${size} / 1024")
message(STATUS "Built target: ${TARGET_PATH}")
message(STATUS "Size: ${size} bytes (${size_kb} KB)")