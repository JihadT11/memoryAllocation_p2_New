cmake_minimum_required(VERSION 3.16)  # ✅ Updated version
project(project2_cpp_template VERSION 1.0 LANGUAGES C CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------
# Download GoogleTest via FetchContent
# ----------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e88cb95b92acbdce9b058dd894a68e1281b38495.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ----------------------------
# Include Paths
# ----------------------------
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/memory_manager
  ${PROJECT_SOURCE_DIR}/src/memory_manager/memory_block
)

# ----------------------------
# Memory Manager Library
# ----------------------------
file(GLOB_RECURSE MEMORY_MANAGER_SOURCES "src/memory_manager/*.cpp")
add_library(memory_manager_lib STATIC ${MEMORY_MANAGER_SOURCES})

# ----------------------------
# File Parser Library
# ----------------------------
file(GLOB_RECURSE FILE_PARSER_SOURCES "src/file_parser/*.cpp")
add_library(file_parser_lib STATIC ${FILE_PARSER_SOURCES})

# ----------------------------
# Main Executable
# ----------------------------
add_executable(memory_manager_exe src/main.cpp)
target_link_libraries(memory_manager_exe PRIVATE memory_manager_lib file_parser_lib)

# ----------------------------
# Add Subdirectory for Tests
# ----------------------------
enable_testing()
add_subdirectory(tests)
