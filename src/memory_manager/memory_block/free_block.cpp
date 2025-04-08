#include "free_block.hpp"
#include "memory_block.hpp"

FreeBlock::FreeBlock(int start, int size) {
    this->start = start;
    this->size = size;
}

int FreeBlock::get_start() const {
    return this->start;
}

int FreeBlock::get_size() const {
    return this->size;
}
