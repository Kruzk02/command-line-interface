#include "../include/cdCommand.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include "../include/CommandContext.h"

void cdCommand::execute(CommandContext &ctx) {
  if (!ctx.arguments.empty()) {
    std::string folder = ctx.arguments.at(0);

    if (std::filesystem::exists(folder)) {
      std::string newPath = std::filesystem::absolute(folder);
      std::filesystem::current_path(newPath);

      ctx.currentDirectory = std::filesystem::current_path();
    } else {
      std::cout << "cd: " << folder << ": No such file or directory"
                << std::endl;
    }
  } else {
    const char *homedir = std::getenv("HOME");
    if (homedir) {
      ctx.currentDirectory = homedir;
    }
  }
}
