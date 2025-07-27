#ifndef CDCOMMAND_H
#define CDCOMMAND_H

#include "Command.h"
#include "CommandContext.h"

class cdCommand : public Command {
 public:
  void execute(const CommandContext& ctx) override;
};
#endif  // !DEBUG
