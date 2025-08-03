#include "../include/ListCommand.h"

#include <filesystem>
#include <iostream>
#include <string>

void ListCommand::execute(CommandContext& ctx) {
  std::string currentDirectory = ctx.currentDirectory;
  for (const auto& entry :
       std::filesystem::directory_iterator(currentDirectory)) {
    std::string directory =
        entry.path().string().substr(currentDirectory.size() + 1);

    if (!ctx.arguments.empty()) {
      if (ctx.arguments[0] == "-a") {
        std::cout << directory << std::endl;
      }
    } else {
      if (directory.at(0) != '.') {
        std::cout << directory << std::endl;
      }
    }
  }
}
