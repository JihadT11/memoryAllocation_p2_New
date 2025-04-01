#include "allocated_block.hpp"

AllocatedBlock::AllocatedBlock(int size, int start, int id) {
    this->start = start;
    this->size= size;
    this->id = id;
}
