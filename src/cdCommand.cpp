#include "../include/cdCommand.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include "../include/CommandContext.h"

void cdCommand::execute(CommandContext &ctx) {
  if (ctx.arguments.empty()) {
    const char *homedir = std::getenv("HOME");
    if (homedir) {
      ctx.currentDirectory = homedir;
      std::filesystem::current_path(homedir);
    }
    return;
  }

  std::string folder = ctx.arguments.at(0);

  if (!std::filesystem::exists(folder)) {
    std::cout << "cd: " << folder << ": No such file or directory" << std::endl;
    return;
  }
  std::string newPath = std::filesystem::absolute(folder);
  std::filesystem::current_path(newPath);

  ctx.currentDirectory = std::filesystem::current_path();
}
