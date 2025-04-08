#ifndef MemoryBlock_H
#define MemoryBlock_H

class MemoryBlock {
  public:
    int start;
    int size;

    virtual int get_start() const = 0;
    virtual int get_size() const = 0;
    virtual ~MemoryBlock() = default; // also add virtual destructor

};
#endif // !MemoryBlock
