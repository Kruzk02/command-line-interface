#include "../include/ListCommand.h"

#include <chrono>
#include <cstdint>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

uintmax_t get_directory_size(const fs::path& dir) {
  uintmax_t size = 0;

  if (fs::exists(dir)) {
    if (fs::is_directory(dir)) {
      for (const auto& entry : fs::directory_iterator(dir)) {
        if (fs::is_regular_file(entry)) {
          size += fs::file_size(entry);
        }
      }
    } else {
      size += fs::file_size(dir);
    }
  }
  return size;
}

std::tm* getFileLastModificationTime(std::string directory) {
  fs::file_time_type ftime = fs::last_write_time(directory);

  auto time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
      ftime - fs::file_time_type::clock::now() +
      std::chrono::system_clock::now());

  std::time_t cftime = std::chrono::system_clock::to_time_t(time);

  return std::localtime(&cftime);
}

void ListCommand::execute(CommandContext& ctx) {
  std::string currentDirectory = ctx.currentDirectory;
  for (const auto& entry : fs::directory_iterator(currentDirectory)) {
    std::string directory =
        entry.path().string().substr(currentDirectory.size() + 1);

    if (!ctx.arguments.empty()) {
      if (ctx.options.is_show_hidden) {
        std::cout << directory << std::endl;
      }

      if (ctx.options.is_list_information) {
        if (!ctx.options.is_show_hidden) {
          fs::file_status status = fs::status(directory);
          fs::perms p = status.permissions();

          std::tm* timeInfo = getFileLastModificationTime(directory);

          std::cout
              << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
              << "\t" << get_directory_size(directory) << "\t"
              << std::put_time(timeInfo, "%m %d %H:%M") << "\t" << directory
              << std::endl;
        }
      }
    } else {
      if (directory.at(0) != '.') {
        std::cout << directory << std::endl;
      }
    }
  }
}
