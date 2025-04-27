#ifndef ALLOCATED_BLOCK_HPP
#define ALLOCATED_BLOCK_HPP

#include "memory_block.hpp"
#include <cstddef>

class AllocatedBlock : public MemoryBlock {
public:
    /** 
     * @param capacity     total capacity (power-of-two) of this block 
     * @param start        start index in the big buffer
     * @param id           unique block ID
     * @param actual_size  number of bytes actually stored
     */
    AllocatedBlock(int capacity, int start, int id, size_t actual_size);

    int     get_start() const override;
    int     get_size()  const override;
    int     get_id()    const;
    size_t  get_actual_size() const;
    void    set_actual_size(size_t new_size);

private:
    int     start;         ///< start offset in the buffer
    int     capacity;      ///< total capacity (power-of-two)
    int     id;            ///< unique block identifier
    size_t  actual_size;   ///< how many bytes of real data are stored
};

#endif // ALLOCATED_BLOCK_HPP
