#include <iostream>
#include <ostream>
#include <regex>
#include <string>

void parseInput(std::string input) {
  std::regex words_regex(R"([^ ="]+|"[^"]+"|=)");
  for (auto i = std::sregex_iterator(input.begin(), input.end(), words_regex);
       i != std::sregex_iterator(); i++) {
    std::string token = (*i).str();
    if (token[0] == '"') {
      token = token.substr(1, token.length() - 2);
    }
    std::cout << token << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::string name;

  std::cout << "Please, enter your full name: ";
  std::getline(std::cin, name);
  std::cout << "Hello, " << name << std::endl;
  parseInput(name);
}
