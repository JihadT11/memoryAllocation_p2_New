#ifndef Command_H
#define Command_H

#include <string>
#include <vector>
class Command {
public:
  std::string function;
  std::vector<std::string> parameters;

  Command();
  ~Command();
};
#endif // !Command
