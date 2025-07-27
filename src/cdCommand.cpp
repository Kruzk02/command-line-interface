#include "../include/cdCommand.h"

#include <filesystem>
#include <iostream>

#include "../include/CommandContext.h"

void cdCommand::execute(const CommandContext& ctx) {
  std::string folder = ctx.arguments.at(0);

  if (std::filesystem::exists(folder)) {
    std::string newPath = std::filesystem::absolute(folder);
    std::filesystem::current_path(newPath);
  } else {
    std::cout << "cd: " << folder << ": No such file or directory" << std::endl;
  }
}
