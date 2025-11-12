/*
This program reads an unsigned integer "a" from the user and computes
floor(log2(a)).
*/

#include <iostream>
#include <sstream>

int main() {
  size_t a;
  std::cin >> a;

  size_t b = a;
  size_t log2 = -1;
  while (b != 0) {
    log2++;
    b = b >> 1;
  }
  std::cout << "a = " << a << ", log2(a) = " << log2 << std::endl;
  return 0;
}
