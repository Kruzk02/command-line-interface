#include <sys/wait.h>
#include <unistd.h>

#include <cctype>
#include <cstdio>
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
#include "../include/Parser.h"
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
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork failed");
    } else if (pid == 0) {
      std::vector<char *> args;
      for (auto &s : inputs) {
        args.push_back(const_cast<char *>(s.c_str()));
      }
      args.push_back(nullptr);

      if (execvp(ctx.command.c_str(), args.data()) == -1) {
        std::cout << ctx.command << ": Command not found." << std::endl;
        exit(1);
      }
    } else {
      int status;
      wait(&status);
    }
    return {};
  }

  Parser parser;
  parser.parse_options(inputs, ctx);
  ctx.arguments.clear();
  parser.parse_arguments(inputs, ctx);

  Command *cmd = commandMap[ctx.command]();

  invoker.setCommand(cmd);
  invoker.execute(ctx);
  delete cmd;

  return {};
}
