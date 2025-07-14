#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string name;

  std::cout << "Please, enter your full name: ";
  std::getline(std::cin, name);
  std::cout << "Hello, " << name << std::endl;
}
