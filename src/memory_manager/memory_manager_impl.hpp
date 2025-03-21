#ifndef MemoryManagerImpl_H
#define MemoryManagerImpl_H

#include <cstdint>
#include <vector>
#include "free_block.hpp"
#include "allocated_block.hpp"

class MemoryManagerImpl {

public:
  // I'll let you fill in the return types and parameters
  void read(); 
  void insert();
  void update();
  void del(); //delete is a keyword...
  void dump();

private:
  uint8_t* data;
  std::vector<AllocatedBlock> allocated_blocks;
  std::vector<FreeBlock> free_blocks;
};
#endif // !MemoryManagerImpl_H
