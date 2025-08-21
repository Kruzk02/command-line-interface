#include <cstdlib>
#include <expected>
#include <filesystem>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/HelpCommand.h"
#include "../include/Invoker.h"
#include "../include/ListCommand.h"
#include "../include/Tokenizer.h"
#include "../include/cdCommand.h"

std::unordered_map<std::string, std::function<Command *()>> commandMap;
CommandContext ctx;

std::expected<void, std::string> handle_command(
    Invoker &invoker, const std::vector<std::string> &inputs) {
  if (inputs.empty()) return std::unexpected("Input cannot be empty");

  if (inputs[0] == "exit") {
    std::cout << "exit\n";
    exit(0);
  }

  if (commandMap.find(inputs[0]) == commandMap.end()) {
    return std::unexpected("Command not found");
  }

  ctx.arguments.clear();
  Command *cmd = commandMap[inputs[0]]();

  if (inputs.size() > 1) {
    ctx.arguments.assign(inputs.begin() + 1, inputs.end());
  }

  invoker.setCommand(cmd);
  invoker.execute(ctx);
  delete cmd;

  return {};
}

int main(int argc, char *argv[]) {
  Invoker invoker;

  commandMap["cd"] = []() { return new cdCommand(); };
  commandMap["ls"] = []() { return new ListCommand(); };
  commandMap["help"] = []() { return new HelpCommand(); };

  while (true) {
    if (ctx.currentDirectory.empty())
      ctx.currentDirectory = std::filesystem::current_path().string();
    std::cout << ctx.currentDirectory << "$ ";
    std::string input;

    std::getline(std::cin, input);
    Tokenizer tokenizer(input);
    std::vector<std::string> inputs = tokenizer.tokenize();

    auto result = handle_command(invoker, inputs);
    if (!result) {
      std::cerr << "Error: " << result.error() << std::endl;
    }
  }
}
