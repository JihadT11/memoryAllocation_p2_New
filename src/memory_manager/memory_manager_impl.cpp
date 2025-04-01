#include "memory_manager_impl.hpp"
#include "memory_block/allocated_block.hpp"
#include <iostream>
#include <algorithm> 
#include <cstring>  

MemoryManagerImpl::MemoryManagerImpl() {
    data = new uint8_t[65535];
    free_blocks.push_back(new FreeBlock(0, 65535)); // Start with one big free block
    this->next_id = 0;
}

int MemoryManagerImpl::insert(size_t size, const std::vector<uint8_t>& input_data) {
    return 0;
}

MemoryManagerImpl::~MemoryManagerImpl() {
    delete[] data;
}

