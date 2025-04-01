#ifndef Command_H
#define Command_H

#include <string>
#include <vector>
class Command {
public:
  std::string function; // Enum ?? = switch case
  std::vector<std::string> parameters;

  Command();
  ~Command();
};
#endif // !Command
