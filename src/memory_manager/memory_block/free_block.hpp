#ifndef FreeBlock_H
#define FreeBlock_H

#include "memory_block.hpp"

class FreeBlock : MemoryBlock {
public:
  FreeBlock(int start, int size);
  virtual int get_start();
  virtual int get_size();

};
#endif // !FreeBlock
