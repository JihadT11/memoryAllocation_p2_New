#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <vector>
#include <cstdint>

class MemoryManagerImpl; // Forward declaration

/**
 * @brief High‐level façade for the buddy‐allocator memory manager.
 *
 * Provides simple methods to insert, read, update, delete, and dump
 * memory blocks, delegating all logic to an underlying MemoryManagerImpl.
 */
class MemoryManager {
public:
    /**
     * @brief Construct a new MemoryManager.
     */
    MemoryManager();
    /**
     * @brief Destroy the MemoryManager, freeing any resources.
     */
    ~MemoryManager();

    /**
     * @brief Allocate a new block and store @p data within it.
     *
     * @param size Number of bytes requested.
     * @param data Byte vector to write into the new block.
     * @return int The block ID on success, or -1 if allocation failed.
     */
    int insert(size_t size, const std::vector<uint8_t>& data);
    /**
     * @brief Read the contents of a block.
     *
     * @param id The ID of the block to read.
     */
    void read(int id);
    /**
     * @brief Update the contents of a block.
     *
     * If the new data exceeds the current block's capacity, the block is deleted and reinserted.
     *
     * @param id The ID of the block to update.
     * @param data The new data to store in the block.
     */
    void update(int id, const std::vector<uint8_t>& data);
    /**
     * @brief Delete a block and free its memory.
     *
     * @param id The ID of the block to delete.
     */
    void del(int id);
    /**
     * @brief Dump the current state of the memory manager.
     *
     * Displays all allocated and free blocks in order.
     */
    void dump();

private:
    MemoryManagerImpl* impl;
};

#endif // MEMORYMANAGER_HPP
