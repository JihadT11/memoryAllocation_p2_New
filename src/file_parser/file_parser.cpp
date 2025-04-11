#include "file_parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Helper to tokenize a line (splitting on whitespace).
static std::vector<std::string> tokenize(const std::string &line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Command> FileParser::parseFile(const std::string& filename) {
    std::vector<Command> commands;
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Cannot open file " << filename << "\n";
        return commands;
    }

    std::string line;
    while (std::getline(infile, line)) {
        // Skip empty lines and comments (e.g., starting with '#')
        if (line.empty() || line[0] == '#') continue;

        // Tokenize line
        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty()) continue;

        Command cmd;
        // Determine command type from the first token.
        std::string cmdStr = tokens[0];
        std::transform(cmdStr.begin(), cmdStr.end(), cmdStr.begin(), ::toupper);
        if (cmdStr == "INSERT") {
            cmd.type = CommandType::INSERT;
            if (tokens.size() < 3) {
                std::cerr << "INSERT requires block size and data.\n";
                continue;
            }
            cmd.size = std::stoul(tokens[1]);
            // Convert remaining tokens into data bytes.
            for (size_t i = 2; i < tokens.size(); ++i) {
                int value = std::stoi(tokens[i]);
                cmd.data.push_back(static_cast<uint8_t>(value));
            }
        }
        else if (cmdStr == "READ") {
            cmd.type = CommandType::READ;
            if (tokens.size() != 2) {
                std::cerr << "READ requires a block ID.\n";
                continue;
            }
            cmd.id = std::stoi(tokens[1]);
        }
        else if (cmdStr == "UPDATE") {
            cmd.type = CommandType::UPDATE;
            if (tokens.size() < 3) {
                std::cerr << "UPDATE requires block ID and new data.\n";
                continue;
            }
            cmd.id = std::stoi(tokens[1]);
            for (size_t i = 2; i < tokens.size(); ++i) {
                int value = std::stoi(tokens[i]);
                cmd.data.push_back(static_cast<uint8_t>(value));
            }
        }
        else if (cmdStr == "DELETE") {
            cmd.type = CommandType::DELETE;
            if (tokens.size() != 2) {
                std::cerr << "DELETE requires a block ID.\n";
                continue;
            }
            cmd.id = std::stoi(tokens[1]);
        }
        else if (cmdStr == "DUMP") {
            cmd.type = CommandType::DUMP;
        }
        else {
            cmd.type = CommandType::INVALID;
            std::cerr << "Invalid command: " << tokens[0] << "\n";
        }

        commands.push_back(cmd);
    }
    return commands;
}
