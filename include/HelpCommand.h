#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "Command.h"
#include "CommandContext.h"

class HelpCommand : public Command {
 public:
  void execute(CommandContext& ctx) override;
};

#endif  // !HELPCOMMAND_H
