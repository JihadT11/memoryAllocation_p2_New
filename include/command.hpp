#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <cstdint>
#include <string>

/**
 * @brief All supported command types for the memory manager.
 */
enum class CommandType {
    INSERT,
    READ,
    UPDATE,
    DELETE,
    DUMP,
    INVALID
};

/**
 * @brief Represents one parsed command along with its parameters.
 *
 * Depending on @c type, different fields are used:
 * - INSERT:  uses @c size and @c data  
 * - READ:    uses @c id  
 * - UPDATE:  uses @c id and @c data  
 * - DELETE:  uses @c id  
 * - DUMP:    ignores other fields  
 * - INVALID: indicates a parse error
 */
struct Command {
    CommandType type = CommandType::INVALID;
    int id = -1;              // For READ, UPDATE, DELETE commands
    size_t size = 0;          // For INSERT commands
    std::vector<uint8_t> data; // For INSERT and UPDATE commands
};

#endif // COMMAND_HPP
