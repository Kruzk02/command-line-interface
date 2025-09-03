#include <string>
#include <vector>

#pragma once
struct CommandContext {
  enum Options { SHOW_HIDDEN = 1 << 0, LIST_INFORMATION = 2 << 0 };

  std::string command;
  std::vector<std::string> arguments;
  int options;

  std::string currentDirectory;

  void resetOptions() { options = 0; }
};
