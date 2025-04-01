#ifndef AllocatedBlock_H
#define AllocatedBlock_H

#include "memory_block.hpp"

class AllocatedBlock: MemoryBlock {
public:
  AllocatedBlock(int size, int start, int id);
private:
  int id;
};
#endif // !AllocatedBlock
