#include <iostream>
#include "file_parser.hpp"
#include "memory_manager.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command_file.cmmd>\n";
        return 1;
    }

    // Parse the command file.
    FileParser parser;
    std::vector<Command> commands = parser.parseFile(argv[1]);

    // Create MemoryManager.
    MemoryManager memManager;

    // Process each command.
    for (const Command &cmd : commands) {
        switch (cmd.type) {
            case CommandType::INSERT: {
                int id = memManager.insert(cmd.size, cmd.data);
                std::cout << "Inserted block with ID: " << id << "\n";
                break;
            }
            case CommandType::READ: {
                memManager.read(cmd.id);
                break;
            }
            case CommandType::UPDATE: {
                memManager.update(cmd.id, cmd.data);
                break;
            }
            case CommandType::DELETE: {
                memManager.del(cmd.id);
                break;
            }
            case CommandType::DUMP: {
                memManager.dump();
                break;
            }
            default: {
                std::cerr << "Invalid command encountered.\n";
                break;
            }
        }
    }
    return 0;
}
