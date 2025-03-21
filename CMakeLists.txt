# 1. Initialize CMake ---------------
# Minimum CMake version to compile
CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

# Project Information
# More can and should be specified, but this is fine...
project(supplement1 VERSION 1.0) 

# make compile_commands.json for our linters' sanity...
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# We will be doing testing, and all tests are in the ./tests folder
enable_testing()
add_subdirectory(tests)

# Use C++ version 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 2. Download and setup googletest for unit testing
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e88cb95b92acbdce9b058dd894a68e1281b38495.zip
)

# Windows-specific: do not let googletest override this project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Everyone: allow googletest to be used in CMake
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# 3. Define Build Targets
# Each target is an "output" of compilation.
# We plan on 2-3 outputs:
# - The library
# - The tests for the library
# - An executable binary

add_executable(memory_manager_exe src/main.cpp)

file(GLOB_RECURSE FILE_PARSER_SOURCES "src/file_parser/*")
add_library(file_parser_lib STATIC ${FILE_PARSER_SOURCES})

file(GLOB_RECURSE MEMORY_MANAGER_SOURCES "src/memory_manager/*")
add_library(memory_manager_lib STATIC ${MEMORY_MANAGER_SOURCES})

add_executable(memory_manager_tests tests/memory_manager_test.cpp)
add_executable(file_parser_tests tests/file_parser_test.cpp)


# 4. Configure references
# When we compile the everything, we want all targets to find the header file(s) in ./include/
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/memory_manager)
include_directories(${PROJECT_SOURCE_DIR}/src/memory_manager/memory_block)

# The test executable needs access to GTest and the supplement library
target_link_libraries(memory_manager_tests PRIVATE GTest::gtest_main)
target_link_libraries(memory_manager_tests PRIVATE memory_manager_lib)

target_link_libraries(file_parser_tests PRIVATE GTest::gtest_main)
target_link_libraries(file_parser_tests PRIVATE file_parser_lib)

# The user executable only needs access to the supplement library
target_link_libraries(memory_manager_exe PRIVATE memory_manager_lib)
target_link_libraries(memory_manager_exe PRIVATE file_parser_lib)

# automagically find the tests in the compiled target
gtest_discover_tests(file_parser_tests)
gtest_discover_tests(memory_manager_tests)
