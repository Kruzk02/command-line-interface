#ifndef INVOKER_H
#define INVOKER_H

#include "Command.h"
#include "CommandContext.h"
class Invoker {
 private:
  Command* command;

 public:
  Invoker();
  void setCommand(Command* command);
  void execute(CommandContext& ctx);
};

#endif  // !INVOKER_H
