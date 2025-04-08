#ifndef AllocatedBlock_H
#define AllocatedBlock_H

#include "memory_block.hpp"

class AllocatedBlock : public MemoryBlock {
public:
    AllocatedBlock(int size, int start, int id, int actual_size);

    int get_start() const;
    int get_size() const;
    int get_id() const;
    int get_actual_size() const; // NEW

private:
    int start;
    int size;
    int id;
    int actual_size; // NEW
};

#endif // !AllocatedBlock
