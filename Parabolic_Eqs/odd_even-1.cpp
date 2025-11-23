/*
This program reads an unsigned integer "a" from the user and decides whether odd
or even
*/

#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
  size_t a;
  std::cin >> a;

  size_t b = (a >> 1) << 1;
  if (a != b)
    std::cout << "a is odd" << std::endl;
  else
    std::cout << "a is even" << std::endl;

  return 0;
}
