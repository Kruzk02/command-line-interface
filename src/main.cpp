#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

std::map<std::string, std::vector<std::string>> parseInput(std::string input) {
  std::string command;
  std::vector<std::string> arguments;

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

  command = inputs[0];
  for (auto i = inputs.begin() + 1; i != inputs.end(); i++) {
    arguments.push_back(*i);
  }

  return {{command, arguments}};
}

int main(int argc, char *argv[]) {
  std::string input;

  std::getline(std::cin, input);
  std::map<std::string, std::vector<std::string>> wd = parseInput(input);

  for (const auto &pair : wd) {
    std::cout << pair.first << ": ";
    for (auto val : pair.second) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}
