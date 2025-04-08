#include "allocated_block.hpp"

AllocatedBlock::AllocatedBlock(int size, int start, int id, int actual_size)
    : size(size), start(start), id(id), actual_size(actual_size) {}

int AllocatedBlock::get_start() const { return start; }
int AllocatedBlock::get_size() const { return size; }
int AllocatedBlock::get_id() const { return id; }
int AllocatedBlock::get_actual_size() const { return actual_size; } // NEW
