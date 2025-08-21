#pragma once

#include <cstring>
#include <string>
#include <vector>

class Tokenizer {
 public:
  explicit Tokenizer(const std::string& input);
  std::vector<std::string> tokenize();

 private:
  std::string input;
};
