#include "../include/Parser.h"

#include <string>
#include <unordered_map>
#include <vector>

void Parser::parse_options(const std::vector<std::string> &tokens,
                           CommandContext &ctx) {
  static const std::unordered_map<std::string, int> options = {
      {"-a", ctx.SHOW_HIDDEN},
      {"-l", ctx.LIST_INFORMATION},
  };

  for (const auto &token : tokens) {
    auto it = options.find(token);
    if (it != options.end()) {
      ctx.options |= it->second;
    }
  }
}

void Parser::parse_arguments(const std::vector<std::string> &tokens,
                             CommandContext &ctx) {
  if (tokens.size() > 1) {
    ctx.arguments.assign(tokens.begin() + 1, tokens.end());
  }
}
