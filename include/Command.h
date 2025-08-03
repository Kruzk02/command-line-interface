#ifndef COMMAND_H
#define COMMAND_H

#include "CommandContext.h"

class Command {
 public:
  virtual ~Command() = default;
  virtual void execute(CommandContext& ctx) = 0;
};

#endif  // !COMMAND_H
