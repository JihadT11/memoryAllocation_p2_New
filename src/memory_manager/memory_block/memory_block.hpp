#ifndef MemoryBlock_H
#define MemoryBlock_H

class MemoryBlock {
  public:
    int start;
    int size;

    virtual int get_start() = 0;
    virtual int get_size() = 0;
};
#endif // !MemoryBlock
