#include "memory_manager_impl.hpp"
#include "memory_block/allocated_block.hpp"
#include "memory_block/free_block.hpp"
#include <cstddef>
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>

// Constructor for MemoryManagerImpl
MemoryManagerImpl::MemoryManagerImpl() {
    // Allocate the memory buffer of 65,536 bytes
    data = new uint8_t[65536];

    // Initialize free block list with one big free block (the whole memory)
    free_blocks.push_back(new FreeBlock(0, 65536));

    // Initialize the first available ID for allocations
    next_id = 0;
}

// Destructor to free up memory
MemoryManagerImpl::~MemoryManagerImpl() {
    delete[] data; // Deallocate main memory
    // Clean up any dynamic FreeBlock pointers
    for (auto block : free_blocks) {
        delete block;
    }
}

size_t MemoryManagerImpl::nextPowerOfTwo(size_t size) {
    size_t power = 1;
    while (power < size) power *= 2;
    return power;
}


// Find best-fit free block (smallest block that fits the required size)
int MemoryManagerImpl::findFreeBlock(size_t required_size) {
    int best_index = -1;
    size_t smallest_diff = SIZE_MAX;

    for (int i = 0; i < free_blocks.size(); ++i) {
        size_t block_size = free_blocks[i]->get_size();
        if (block_size >= required_size && (block_size - required_size) < smallest_diff) {
            best_index = i;
            smallest_diff = block_size - required_size;
        }
    }
    return best_index; // -1 if no block found
}

// Insert: Allocate memory and store data
int MemoryManagerImpl::insert(size_t size, const std::vector<uint8_t>& input_data) {
    // Round up to the next power of two
    size_t alloc_size = this->nextPowerOfTwo(size);

    // Find suitable free block
    int index = findFreeBlock(alloc_size);
    if (index == -1) return -1; // No space

    FreeBlock* selected = free_blocks[index];

    // Split blocks until the block size matches allocation size
    while (selected->get_size() > alloc_size) {
        size_t half_size = selected->get_size() / 2;
        size_t start = selected->get_start();

        // Create two smaller buddies
        FreeBlock* buddy1 = new FreeBlock(start, half_size);
        FreeBlock* buddy2 = new FreeBlock(start + half_size, half_size);

        // Replace current block with the two buddies
        free_blocks.erase(free_blocks.begin() + index);
        free_blocks.insert(free_blocks.begin() + index, buddy2);
        free_blocks.insert(free_blocks.begin() + index, buddy1);

        selected = free_blocks[index]; // Continue splitting if needed
    }

    // At this point, we have an exact-size block
    size_t start_addr = selected->get_start();
    memcpy(data + start_addr, input_data.data(), size); // Copy actual data

    // Create allocated block and track it
    AllocatedBlock new_block(alloc_size, start_addr, next_id, size);
    allocated_blocks.push_back(new_block);

    // Remove used block from free list
    free_blocks.erase(free_blocks.begin() + index);

    // Return current ID, then increment for next use
    return next_id++;
}

void MemoryManagerImpl::read(int id) {
    for (const auto& block : allocated_blocks) { 
        if (block.get_id() == id) {
            std::cout << "Block ID: " << block.get_id() << "\n";
            std::cout << "Start Address: " << block.get_start() << "\n";
            std::cout << "Size: " << block.get_size() << "\n";
           std::cout << "Data: ";
            for (size_t i = 0; i < block.get_actual_size(); ++i) {
                std::cout << static_cast<int>(data[block.get_start() + i]) << " ";
            }
            std::cout << std::endl;

            return;
        }
    }

    std::cerr << "Error: Block ID not found.\n";
}

void MemoryManagerImpl::tryCoalesce(FreeBlock* block) {
    for (auto it = free_blocks.begin(); it != free_blocks.end(); ++it) {
        FreeBlock* buddy = *it;

        if (buddy == block) continue;

        if (buddy->get_size() == block->get_size()) {
            size_t buddy_start = buddy->get_start();
            size_t block_start = block->get_start();
            size_t size = block->get_size();

            // Check if they're buddies
            if ((buddy_start ^ size) == block_start) {
                // Found a buddy — merge
                size_t merged_start = std::min(block_start, buddy_start);
                FreeBlock* merged = new FreeBlock(merged_start, size * 2);

                // Remove old blocks
                free_blocks.erase(std::remove(free_blocks.begin(), free_blocks.end(), block), free_blocks.end());
                free_blocks.erase(std::remove(free_blocks.begin(), free_blocks.end(), buddy), free_blocks.end());
                delete block;
                delete buddy;

                // Add new merged block and recurse
                free_blocks.push_back(merged);
                tryCoalesce(merged);
                return;
            }
        }
    }
}

void MemoryManagerImpl::update(int id, const std::vector<uint8_t>& input_data) {
    for (auto it = allocated_blocks.begin(); it != allocated_blocks.end(); ++it) {
        if (it->get_id() == id) {
            size_t start_addr = it->get_start();
            size_t block_capacity = it->get_size();
            
            // Check if the new data exceeds the current block's capacity.
            if (input_data.size() > block_capacity) {
                std::cout << "Block " << id << " requires more space. Deleting and reinserting..." << std::endl;
                // Remove the existing allocation and free the space.
                del(id);
                // Insert the new data. The insert method rounds the new size up to the next power of two.
                int new_id = insert(input_data.size(), input_data);
                if (new_id < 0) {
                    std::cerr << "Reinsertion failed: no available memory." << std::endl;
                } else {
                    std::cout << "Block " << id << " updated by deletion and reinsertion as block " << new_id << std::endl;
                }
                return;
            }
            
            // If the data fits, update in place.
            memcpy(data + start_addr, input_data.data(), input_data.size());
            it->set_actual_size(input_data.size());
            std::cout << "Block " << id << " updated in place." << std::endl;
            return;
        }
    }
    std::cerr << "Error: Block ID not found." << std::endl;
}


void MemoryManagerImpl::del(int id) {
    // Step 1: Find and remove the allocated block
    for (auto it = allocated_blocks.begin(); it != allocated_blocks.end(); ++it) {
        if (it->get_id() == id) {
            size_t start = it->get_start();
            size_t size = it->get_size();

            // Step 2: Create new free block and add it
            FreeBlock* freed = new FreeBlock(start, size);
            free_blocks.push_back(freed);

            // Step 3: Remove allocated block
            allocated_blocks.erase(it);

            // Step 4: Try merging with buddy blocks
            tryCoalesce(freed);
            return;
        }
    }

    std::cerr << "Nothing at [" << id << "]\n";
}

// Dump the state of the memory manager: display all allocated and free blocks in order.
void MemoryManagerImpl::dump() {
    // Vector to hold pointers to all memory blocks (both allocated and free)
    std::vector<MemoryBlock*> allBlocks;

    // Add allocated blocks (stored by value, so we take their address).
    for (auto& block : allocated_blocks) {
        allBlocks.push_back(&block);
    }
    
    // Add free blocks (which are already pointers).
    for (FreeBlock* block : free_blocks) {
        allBlocks.push_back(block);
    }
    
    // Sort all blocks by their starting address.
    std::sort(allBlocks.begin(), allBlocks.end(), [](MemoryBlock* a, MemoryBlock* b) {
        return a->get_start() < b->get_start();
    });
    
    // Print a header for clarity.
    std::cout << "Dumping Memory Manager State:\n";
    
    // Iterate through the sorted blocks and print their details.
    for (MemoryBlock* block : allBlocks) {
        int start = block->get_start();
        int blockSize = block->get_size();
        
        // Use dynamic_cast to check if the block is an allocated block.
        AllocatedBlock* allocated = dynamic_cast<AllocatedBlock*>(block);
        if (allocated != nullptr) {
            // Allocated block: print its ID, start address (in hex) and allocated capacity (in decimal)
            std::cout << "Address: 0x" << std::hex << start << std::dec
                      << " Status: ALLOCATED, ID: " << allocated->get_id()
                      << ", Capacity: " << blockSize << "\n";
            
            // Also print the actual stored data.
            std::cout << "  Data: ";
            // Assumes get_actual_size() returns number of bytes stored.
            size_t actualSize = allocated->get_actual_size();
            for (size_t i = 0; i < actualSize; ++i) {
                // Print each byte as an integer for readability.
                std::cout << static_cast<char>(data[start + i]);
            }
            std::cout << "\n";
        } else {
            // Free block: print start address and block size.
            std::cout << "Address: 0x" << std::hex << start << std::dec
                      << " Status: FREE, Size: " << blockSize << "\n";
        }
    }
}
