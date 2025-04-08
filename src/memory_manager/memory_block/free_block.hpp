#ifndef FREEBLOCK_H
#define FREEBLOCK_H

#include "memory_block.hpp"

class FreeBlock : public MemoryBlock {
public:
    FreeBlock(int start, int size);

    int get_start() const override;
    int get_size() const override;

private:
    int start;
    int size;
};

#endif // FREEBLOCK_H
