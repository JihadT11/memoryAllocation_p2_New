#include "allocated_block.hpp"

AllocatedBlock::AllocatedBlock(int capacity,
                               int start,
                               int id,
                               size_t actual_size)
  : start(start)
  , capacity(capacity)
  , id(id)
  , actual_size(actual_size)
{}

int AllocatedBlock::get_start() const {
    return start;
}

int AllocatedBlock::get_size() const {
    return capacity;
}

int AllocatedBlock::get_id() const {
    return id;
}

size_t AllocatedBlock::get_actual_size() const {
    return actual_size;
}

void AllocatedBlock::set_actual_size(size_t new_size) {
    actual_size = new_size;
}
