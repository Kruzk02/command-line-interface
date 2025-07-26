#include <string>
#include <vector>

#pragma once

struct CommandContext {
  std::vector<std::string> arguments;
  std::string currentDirectory;
};
