#include "../include/HelpCommand.h"

#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::string> commands = {
    {"ls", "List files"},
    {"cd", "Change directory"},
    {"exit", "Exit the shell"},
    {"help", "Diplay help information for all commands or a specific one."}};

void HelpCommand::execute(const CommandContext& ctx) {
  std::cout << "Available commands:" << std::endl;
  for (auto& command : commands) {
    std::cout << std::string(5, ' ') << command.first << ": " << command.second
              << std::endl;
  }
}
