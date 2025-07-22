#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> parse_input(const std::string &input) {
  if (input.empty()) return {};

  std::vector<std::string> inputs;
  std::regex words_regex(R"([^ ="]+|"[^"]+"|=)");

  for (auto i = std::sregex_iterator(input.begin(), input.end(), words_regex);
       i != std::sregex_iterator(); ++i) {
    std::string token = (*i).str();
    if (token[0] == '"') {
      token = token.substr(1, token.length() - 2);
    }

    inputs.push_back(token);
  }

  return inputs;
}

void handle_change_directory(std::string folder) {
  if (std::filesystem::exists(folder)) {
    std::string newPath = std::filesystem::absolute(folder);
    std::filesystem::current_path(newPath);
  } else {
    std::cout << "cd: " << folder << ": No such file or directory" << std::endl;
  }
}

void handle_list_command(std::string argument) {
  for (const auto &entry : std::filesystem::directory_iterator(".")) {
    std::string directory = entry.path().string().substr(2);

    if (argument == "-a") {
      std::cout << directory << std::endl;
    } else {
      if (directory.at(0) == '.') {
        continue;
      } else {
        std::cout << directory << std::endl;
      }
    }
  }
}

void handle_command(std::vector<std::string> inputs) {
  if (inputs[0] == "cd") {
    if (inputs.size() - 1 >= 2) {
      std::cout << "cd: too many arguments " << std::endl;
    }

    handle_change_directory(inputs[1]);
  } else if (inputs[0] == "ls") {
    handle_list_command(inputs[1]);
  } else if (inputs[0] == "exit") {
    exit(0);
  } else {
    std::cout << inputs[0] << ": command not found" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  while (true) {
    std::cout << std::filesystem::current_path().string() << "$ ";
    std::string input;

    std::getline(std::cin, input);
    std::vector<std::string> inputs = parse_input(input);

    handle_command(inputs);
  }
}
