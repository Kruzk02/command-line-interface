#include "../include/Invoker.h"

Invoker::Invoker() : command(nullptr) {}

void Invoker::setCommand(Command* cmd) { command = cmd; }

void Invoker::execute(CommandContext& ctx) {
  if (command) command->execute(ctx);
}
