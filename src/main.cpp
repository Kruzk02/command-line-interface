#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> parseInput(std::string input) {
  if (input.empty())
    return {};
  std::vector<std::string> inputs;

  std::regex words_regex(R"([^ ="]+|"[^"]+"|=)");
  for (auto i = std::sregex_iterator(input.begin(), input.end(), words_regex);
       i != std::sregex_iterator(); i++) {
    std::string token = (*i).str();
    if (token[0] == '"') {
      token = token.substr(1, token.length() - 2);
    }

    inputs.push_back(token);
  }

  return inputs;
}

int main(int argc, char *argv[]) {
  std::string input;

  std::getline(std::cin, input);
  std::vector<std::string> inputs = parseInput(input);

  for (const auto command : inputs) {
    std::cout << command << std::endl;
  }
}
