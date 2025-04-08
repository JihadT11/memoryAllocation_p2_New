#pragma once
#include <vector>
#include <string>
#include <cstdint>

enum class CommandType {
    INSERT,
    READ,
    UPDATE,
    DELETE,
    DUMP,
    INVALID
};

struct Command {
    CommandType type;
    int id = -1;
    size_t size = 0;
    std::vector<uint8_t> data;
};
