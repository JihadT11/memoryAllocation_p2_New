# GoogleTest already provided by parent CMakeLists.txt
enable_testing()

add_executable(memory_manager_tests
  memory_manager_test.cpp
)

target_link_libraries(memory_manager_tests
  GTest::gtest_main
  memory_manager_lib
)

include(GoogleTest)
gtest_discover_tests(memory_manager_tests)
