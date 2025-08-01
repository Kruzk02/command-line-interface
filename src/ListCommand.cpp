#include "../include/ListCommand.h"

#include <filesystem>
#include <iostream>

void ListCommand::execute(const CommandContext& ctx) {
  for (const auto& entry : std::filesystem::directory_iterator(".")) {
    std::string directory = entry.path().string().substr(2);

    if (!ctx.arguments.empty()) {
      if (ctx.arguments[0] == "-a") {
        std::cout << directory << std::endl;
      }
    } else {
      if (directory.at(0) == '.') {
        continue;
      } else {
        std::cout << directory << std::endl;
      }
    }
  }
}
