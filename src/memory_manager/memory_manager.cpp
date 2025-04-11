#include "memory_manager.hpp"
#include "memory_manager_impl.hpp"

MemoryManager::MemoryManager() {
    impl = new MemoryManagerImpl();
}

MemoryManager::~MemoryManager() {
    delete impl;
}

int MemoryManager::insert(size_t size, const std::vector<uint8_t>& data) {
    return impl->insert(size, data);
}

void MemoryManager::read(int id) {
    impl->read(id);
}

void MemoryManager::update(int id, const std::vector<uint8_t>& data) {
    impl->update(id, data);
}

void MemoryManager::del(int id) {
    impl->del(id);
}

void MemoryManager::dump() {
    impl->dump();
}
