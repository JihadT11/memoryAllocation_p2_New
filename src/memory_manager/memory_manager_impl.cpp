#include "memory_manager_impl.hpp"
#include <iostream>
#include <algorithm> 
#include <cstring>  

MemoryManagerImpl::MemoryManagerImpl() {
    data = new uint8_t[65535];
    free_blocks.emplace_back(0, 65535); // Start with one big free block
}

MemoryManagerImpl::MemoryManagerImpl() {
    delete[] data;
}

