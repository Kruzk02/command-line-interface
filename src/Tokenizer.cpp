#include "../include/Tokenizer.h"

#include <regex>
#include <string>
#include <vector>

std::vector<std::string> Tokenizer::parse_input(const std::string &input) {
  if (input.empty()) return {};

  std::vector<std::string> inputs;
  std::regex words_regex(R"([^ ="]+|"[^"]+"|=)");

  for (auto i = std::sregex_iterator(input.begin(), input.end(), words_regex);
       i != std::sregex_iterator(); ++i) {
    std::string token = (*i).str();
    if (token[0] == '"') {
      token = token.substr(1, token.length() - 2);
    }

    inputs.push_back(token);
  }

  return inputs;
}
