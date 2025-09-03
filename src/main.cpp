#include <cctype>
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

std::unordered_map<std::string, std::function<Command *()>> commandMap = {
    {"cd", []() { return new cdCommand(); }},
    {"ls", []() { return new ListCommand(); }},
    {"help", []() { return new HelpCommand(); }}};

CommandContext ctx;

std::expected<void, std::string> handle_command(
    Invoker &invoker, const std::vector<std::string> &inputs);

int main(int argc, char *argv[]) {
  Invoker invoker;

  while (true) {
    ctx.resetOptions();
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

std::expected<void, std::string> validate_inputs(
    const std::vector<std::string> &inputs) {
  if (inputs.empty()) return std::unexpected("Input cannot be empty");
  return {};
}

void parse_options(const std::vector<std::string> &inputs,
                   CommandContext &ctx) {
  for (const auto &token : inputs) {
    if (token == "-a")
      ctx.options |= ctx.SHOW_HIDDEN;
    else if (token == "-l")
      ctx.options |= ctx.LIST_INFORMATION;
  }
}

void parse_arguments(const std::vector<std::string> &inputs,
                     CommandContext &ctx) {
  if (inputs.size() > 1) {
    ctx.arguments.assign(inputs.begin() + 1, inputs.end());
  }
}

bool handle_builtin(const std::string &command) {
  if (command == "exit") {
    std::cout << "exit" << std::endl;
    exit(1);
  }
  return false;
}

std::expected<void, std::string> handle_command(
    Invoker &invoker, const std::vector<std::string> &inputs) {
  if (auto validation = validate_inputs(inputs); !validation) {
    return validation;
  }

  if (handle_builtin(inputs[0])) {
    return {};
  }

  ctx.command = inputs[0];

  if (commandMap.find(ctx.command) == commandMap.end()) {
    return std::unexpected("Command not found");
  }

  parse_options(inputs, ctx);
  ctx.arguments.clear();
  parse_arguments(inputs, ctx);

  Command *cmd = commandMap[ctx.command]();

  invoker.setCommand(cmd);
  invoker.execute(ctx);
  delete cmd;

  return {};
}
