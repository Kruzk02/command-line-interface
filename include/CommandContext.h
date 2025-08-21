#include <string>
#include <vector>

#pragma once
struct CommandContext {
  struct Options {
    bool is_show_hidden;
    bool is_list_information;
  };

  std::string command;
  std::vector<std::string> arguments;
  Options options;

  std::string currentDirectory;
};
