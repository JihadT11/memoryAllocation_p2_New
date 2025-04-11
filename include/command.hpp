#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <cstdint>
#include <string>

enum class CommandType {
    INSERT,
    READ,
    UPDATE,
    DELETE,
    DUMP,
    INVALID
};

struct Command {
    CommandType type = CommandType::INVALID;
    int id = -1;              // For READ, UPDATE, DELETE commands
    size_t size = 0;          // For INSERT commands
    std::vector<uint8_t> data; // For INSERT and UPDATE commands
};

#endif // COMMAND_HPP
