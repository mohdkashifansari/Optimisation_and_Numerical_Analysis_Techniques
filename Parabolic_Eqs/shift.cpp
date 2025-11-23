#include <iostream>

int main() {
  float a;
  std::cout << "float a = ";
  std::cin >> a;
  std::cout << std::endl;
  std::cout << "Bits in memory for a= " << a << ": " << std::endl;
  for (int i=0; i<sizeof(float); i++) {
    char b = *(((char*)(&a))+i);
    char m = 0x01;
    for (int j=0; j<8; ++j) {
      bool p=(b&m);
      std::cout << p << " ";
      m = m << 1;
    }
    std::cout << " ";
  }
  return 0;
}
