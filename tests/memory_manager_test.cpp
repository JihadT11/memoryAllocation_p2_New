#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "memory_manager_impl.hpp"

TEST(MemoryManagerTest, DeleteBlock) {
    MemoryManagerImpl manager;

    std::vector<uint8_t> data = {100, 101, 102};
    int id = manager.insert(data.size(), data);
    ASSERT_GE(id, 0);

    // Capture output before delete
    std::stringstream beforeDelete;
    std::streambuf* cout_old = std::cout.rdbuf(beforeDelete.rdbuf());
    manager.read(id);
    std::cout.rdbuf(cout_old);

    EXPECT_NE(beforeDelete.str().find("Block ID:"), std::string::npos);

    // Delete the block
    manager.del(id);

    // Capture error output after delete (read prints error to std::cerr)
    std::stringstream afterDelete;
    std::streambuf* cerr_old = std::cerr.rdbuf(afterDelete.rdbuf());
    manager.read(id);
    std::cerr.rdbuf(cerr_old);

    EXPECT_NE(afterDelete.str().find("Error: Block ID not found"), std::string::npos);
}

TEST(MemoryManagerTest, InsertAndReadData) {
    MemoryManagerImpl manager;

    std::vector<uint8_t> data = {10, 20, 30, 40};
    int id = manager.insert(data.size(), data);
    ASSERT_GE(id, 0);

    // Capture output from read
    std::stringstream buffer;
    std::streambuf* cout_old = std::cout.rdbuf(buffer.rdbuf());
    manager.read(id);
    std::cout.rdbuf(cout_old);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Block ID: " + std::to_string(id)), std::string::npos);
    EXPECT_NE(output.find("Data: 10 20 30 40 "), std::string::npos);
}

TEST(MemoryManagerTest, UpdateDataInBlock) {
    MemoryManagerImpl manager;

    std::vector<uint8_t> original = {1, 2, 3, 4};
    std::vector<uint8_t> updated = {9, 8, 7, 6};

    int id = manager.insert(original.size(), original);
    ASSERT_GE(id, 0);

    manager.update(id, updated);

    // Capture output from read
    std::stringstream buffer;
    std::streambuf* cout_old = std::cout.rdbuf(buffer.rdbuf());
    manager.read(id);
    std::cout.rdbuf(cout_old);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Data: 9 8 7 6 "), std::string::npos);
}