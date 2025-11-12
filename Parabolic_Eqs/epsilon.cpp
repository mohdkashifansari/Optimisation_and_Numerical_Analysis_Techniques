#include <iostream>

int main() {
  size_t n=0;
  double epsilon=1.0;
  while (1.0 + epsilon > 1.0) {
    epsilon /= 2.0;
    n++;
  }
  std::cout << "Last success for n=" << n-1 << std::endl
            << "epsilon=" << epsilon << std::endl;
  return 0;
}