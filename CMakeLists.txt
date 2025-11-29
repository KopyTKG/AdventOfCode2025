cmake_minimum_required(VERSION 3.22)

project(
	template_cpp23
	VERSION "0.1.0"
	DESCRIPTION "C++23 project template"
	LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR is: ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)

add_custom_target(clean_keep_bin
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning build folder except ${CMAKE_PROJECT_NAME} and ${CMAKE_PROJECT_NAME}.sha256"
    COMMAND find ${CMAKE_BINARY_DIR} -type f ! -name '${CMAKE_PROJECT_NAME}' ! -name '${CMAKE_PROJECT_NAME}.sha256' -delete
    COMMAND find ${CMAKE_BINARY_DIR} -type d -empty -delete
)

