#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

#include "../include/HelpCommand.h"
#include "../include/Invoker.h"
#include "../include/ListCommand.h"
#include "../include/cdCommand.h"

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

void handle_command(std::vector<std::string> inputs) {
  CommandContext ctx;
  Command *cmd = nullptr;
  Invoker *invoker = new Invoker();
  if (inputs[0] == "cd") {
    if (inputs.size() - 1 >= 2) {
      std::cout << "cd: too many arguments " << std::endl;
    } else {
      cmd = new cdCommand();
      ctx.arguments.push_back(inputs[1]);
    }
  } else if (inputs[0] == "ls") {
    cmd = new ListCommand;
    ctx.arguments.push_back(inputs[1]);
  } else if (inputs[0] == "exit") {
    exit(0);
  } else if (inputs[0] == "help") {
    cmd = new HelpCommand();
  } else {
    std::cout << inputs[0] << ": command not found" << std::endl;
  }
  if (cmd) {
    invoker->setCommand(cmd);
    invoker->execute(ctx);
    delete invoker;
    delete cmd;
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
