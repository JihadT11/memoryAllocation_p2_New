#ifndef MemoryManagerImpl_H
#define MemoryManagerImpl_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include <climits>   // for SIZE_MAX

#include "allocated_block.hpp"
#include "free_block.hpp"

/**
 * @brief Implements a buddy allocation memory manager.
 *
 * The MemoryManagerImpl class manages a fixed memory buffer using a buddy allocation scheme.
 * It keeps track of allocated and free blocks, supports insertion, updating, deletion,
 * and can dump the current memory state for debugging.
 */
class MemoryManagerImpl {

public:
    /**
     * @brief Constructs a new MemoryManagerImpl object.
     *
     * Initializes a 65,536-byte memory buffer and sets up an initial free block covering
     * the entire available memory. Also initializes the next available allocation ID.
     */  

  void read(int id); 
    /**
     * @brief Inserts a new memory block with the given data.
     *
     * The requested size is rounded up to the next power of two, and the data is copied into the allocated block.
     *
     * @param size The desired number of bytes for the allocation.
     * @param input_data The data to store in the new block.
     * @return int The unique identifier for the allocated block, or -1 if allocation fails.
     */
  int insert(size_t size, const std::vector<uint8_t>& input_data);
    /**
     * @brief Updates the memory block with the specified ID.
     *
     * If the new data exceeds the block's capacity, the block is deleted and reinserted with the new data.
     *
     * @param id The ID of the block to update.
     * @param input_data The new data to store.
     */
  void update(int id, const std::vector<uint8_t>& input_data);
    /**
     * @brief Deletes the memory block with the specified ID.
     *
     * Frees the block's memory and attempts to merge adjacent free blocks (coalescing).
     *
     * @param id The ID of the block to delete.
     */
  void del(int id); //delete is a keyword...
    /**
     * @brief Dumps the current state of the memory manager.
     *
     * Prints a sorted list of all allocated and free blocks, along with their details.
     */
  void dump();
    /**
     * @brief Finds the best-fit free block for the required size.
     *
     * Searches the free block list for the smallest block that can fit the requested size.
     *
     * @param required_size The number of bytes needed.
     * @return int The index of the free block in the free_blocks vector, or -1 if none found.
     */
  int findFreeBlock(size_t required_size);
  MemoryManagerImpl();
     /**
     * @brief Destroys the MemoryManagerImpl object.
     *
     * Releases the memory buffer and frees all dynamically allocated free block objects.
     */
  ~MemoryManagerImpl();
      /**
     * @brief Reads the memory block with the specified ID.
     *
     * Prints block metadata (ID, start address, capacity) and the stored data.
     *
     * @param id The unique identifier of the memory block to read.
     */
void tryCoalesce(FreeBlock* block);  // add this in private section
    /**
     * @brief Returns the next power of two greater than or equal to the given size.
     *
     * Useful for ensuring memory allocations follow the buddy system rules.
     *
     * @param size The minimum required size.
     * @return size_t The next power of two.
     */

private:
  uint8_t* data;
  std::vector<AllocatedBlock> allocated_blocks;
  std::vector<FreeBlock*> free_blocks;
  size_t nextPowerOfTwo(size_t size);  
  int next_id;


};
#endif // !MemoryManagerImpl_H
