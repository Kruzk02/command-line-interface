#pragma once

#include <string>
#include <vector>

#include "CommandContext.h"
class Parser {
 public:
  void parse_options(const std::vector<std::string> &tokens,
                     CommandContext &ctx);
  void parse_arguments(const std::vector<std::string> &tokens,
                       CommandContext &ctx);
};
