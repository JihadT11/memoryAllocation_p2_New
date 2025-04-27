#include "file_parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// Helper to tokenize a line (splitting on whitespace)
static std::vector<std::string> tokenize(const std::string &line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Helper to determine if a string is a numeric value.
// Returns true if every character is a digit (an optional '-' at start is allowed).
static bool isNumber(const std::string &s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-' && s.size() > 1) {
        start = 1;
    }
    for (size_t i = start; i < s.size(); i++) {
        if (!std::isdigit(s[i])) {
            return false;
        }
    }
    return true;
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
        line.erase(std::remove(line.begin(), line.end(), ';'), line.end());
        if (line.empty() || line[0] == '#') continue;

        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty()) continue;

        Command cmd;
        // Determine command type based on the first token (uppercase)
        std::string cmdStr = tokens[0];
        std::transform(cmdStr.begin(), cmdStr.end(), cmdStr.begin(), ::toupper);
        if (cmdStr == "INSERT") {
            cmd.type = CommandType::INSERT;
            if (tokens.size() < 3) {
                std::cerr << "INSERT requires block size and data.\n";
                continue;
            }
            cmd.size = std::stoul(tokens[1]);
            // Process each remaining token: numeric or string
            for (size_t i = 2; i < tokens.size(); ++i) {
                if (isNumber(tokens[i])) {
                    cmd.data.push_back(static_cast<uint8_t>(std::stoi(tokens[i])));
                } else {
                    for (char c : tokens[i]) {
                        cmd.data.push_back(static_cast<uint8_t>(c));
                    }
                }
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
                if (isNumber(tokens[i])) {
                    cmd.data.push_back(static_cast<uint8_t>(std::stoi(tokens[i])));
                } else {
                    for (char c : tokens[i]) {
                        cmd.data.push_back(static_cast<uint8_t>(c));
                    }
                }
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
