#include "../include/Parser.h"

#include <string>
#include <vector>

void Parser::parse_options(const std::vector<std::string> &tokens,
                           CommandContext &ctx) {
  for (const auto &token : tokens) {
    if (token == "-a")
      ctx.options |= ctx.SHOW_HIDDEN;
    else if (token == "-l")
      ctx.options |= ctx.LIST_INFORMATION;
  }
}

void Parser::parse_arguments(const std::vector<std::string> &tokens,
                             CommandContext &ctx) {
  if (tokens.size() > 1) {
    ctx.arguments.assign(tokens.begin() + 1, tokens.end());
  }
}
