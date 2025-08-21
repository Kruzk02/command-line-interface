#include "../include/Tokenizer.h"

#include <regex>
#include <string>
#include <vector>

Tokenizer::Tokenizer(const std::string& input) : input(input) {}

std::vector<std::string> Tokenizer::tokenize() {
  if (input.empty()) return {};

  std::vector<std::string> tokens;
  std::regex words_regex(R"([^ ="]+|"[^"]+"|=)");

  for (auto i = std::sregex_iterator(input.begin(), input.end(), words_regex);
       i != std::sregex_iterator(); i++) {
    std::string token = (*i).str();
    if (token[0] == '"') {
      token = token.substr(1, token.length() - 2);
    }

    tokens.push_back(token);
  }
  return tokens;
}
