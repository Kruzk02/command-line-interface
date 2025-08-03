#ifndef LISTCOMMAND_H
#define LISTCOMMAND_H

#include "Command.h"
#include "CommandContext.h"

class ListCommand : public Command {
 public:
  void execute(CommandContext& ctx) override;
};
#endif
