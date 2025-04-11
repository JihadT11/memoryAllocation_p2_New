#ifndef FILEPARSER_HPP
#define FILEPARSER_HPP

#include "command.hpp"
#include <string>
#include <vector>

class FileParser {
public:
    // Parses the given file and returns a list of commands.
    std::vector<Command> parseFile(const std::string& filename);
};

#endif // FILEPARSER_HPP
