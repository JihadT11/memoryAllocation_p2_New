#ifndef FILEPARSER_HPP
#define FILEPARSER_HPP

#include "command.hpp"
#include <string>
#include <vector>

/**
 * @brief Parses a sequence of text commands from a file.
 *
 * Opens the file at @p filename, ignores empty lines and comments (lines
 * starting with '#'), strips out any semicolons, tokenizes each line on
 * whitespace, and converts recognized commands into Command structs.
 */
class FileParser {
public:
    /**
     * @brief Parse the given file into a list of commands.
     *
     * @param filename Path to the .cmmd (or .txt) file containing commands.
     * @return std::vector<Command> A vector of parsed Command objects.  
     *                              Any invalid lines become CommandType::INVALID.
     */
    // Parses the given file and returns a list of commands.
    std::vector<Command> parseFile(const std::string& filename);
};

#endif // FILEPARSER_HPP
