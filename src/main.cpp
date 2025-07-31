#include <cstdlib>
#include <filesystem>
#include <functional>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/HelpCommand.h"
#include "../include/Invoker.h"
#include "../include/ListCommand.h"
#include "../include/cdCommand.h"

std::unordered_map<std::string, std::function<Command *()>> commandMap;

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

void handle_command(Invoker &invoker, std::vector<std::string> inputs) {
  CommandContext ctx;
  Command *cmd = nullptr;
  if (commandMap.find(inputs[0]) != commandMap.end()) {
    cmd = commandMap[inputs[0]]();

    if (inputs.size() > 1) {
      ctx.arguments.assign(inputs.begin() + 1, inputs.end());
    } else {
      ctx.arguments.push_back(inputs[1]);
    }

    invoker.setCommand(cmd);
    invoker.execute(ctx);
    delete cmd;
  } else {
    std::cout << inputs[0] << ": command not found\n";
  }
}

int main(int argc, char *argv[]) {
  Invoker invoker;

  commandMap["cd"] = []() { return new cdCommand(); };
  commandMap["ls"] = []() { return new ListCommand(); };
  commandMap["help"] = []() { return new HelpCommand(); };

  while (true) {
    std::cout << std::filesystem::current_path().string() << "$ ";
    std::string input;

    std::getline(std::cin, input);
    std::vector<std::string> inputs = parse_input(input);

    handle_command(invoker, inputs);
  }
}
