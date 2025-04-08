#include "memory_manager_impl.hpp"
#include <vector>

int main() {
    MemoryManagerImpl manager;

    std::vector<uint8_t> test_data = {'H', 'e', 'l', 'l', 'o'};
    manager.insert(test_data.size(), test_data);

    manager.dump();  // You can add this next!

    return 0;
}
