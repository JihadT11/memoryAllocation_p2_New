#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <vector>
#include <cstdint>

class MemoryManagerImpl; // Forward declaration

class MemoryManager {
public:
    MemoryManager();
    ~MemoryManager();

    // Facade methods – these can forward the parameters to your implementation.
    int insert(size_t size, const std::vector<uint8_t>& data);
    void read(int id);
    void update(int id, const std::vector<uint8_t>& data);
    void del(int id);
    void dump();

private:
    MemoryManagerImpl* impl;
};

#endif // MEMORYMANAGER_HPP
