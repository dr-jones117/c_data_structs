
cmake_minimum_required(VERSION 3.10)
project(mish)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # does not produce the json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include directories
include_directories(include /usr/include)

# Add source files
file(GLOB SOURCES "src/*.c")

# Generate executable
add_executable(mish ${SOURCES})

# Link against readline library
target_link_libraries(mish readline)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
