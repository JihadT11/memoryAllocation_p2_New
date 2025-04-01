#ifndef MemoryManagerImpl_H
#define MemoryManagerImpl_H

#include <cstdint>
#include <vector>
#include "allocated_block.hpp"

class MemoryManagerImpl {

public:
  // I'll let you fill in the return types and parameters
  void read(int id); 
  void insert(size_t size, const std::vector<uint8_t>& input_data);
  void update(int id, const std::vector<uint8_t>& input_data);
  void del(int id); //delete is a keyword...
  void dump();

private:
  uint8_t* data;
  std::vector<AllocatedBlock> allocated_blocks;
  std::vector<FreeBlock> free_blocks;
  size_t nextPowerOfTwo(size_t size);  
  int next_id;

};
#endif // !MemoryManagerImpl_H
