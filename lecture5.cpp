#include <iostream>

int main() {

    float a;
    std::cout << "Enter a floating-point number: ";
    std::cin >> a;

    std::cout << std::endl << "Bits in memory representation: "<< a << " = "<< std::endl; 
    for (size_t i = 0; i < sizeof(float); ++i) {
        char b= * (((char*) &a)+i);
        char m = 0x01;

        for (int j = 0; j < 8; ++j) {
            bool p = (b & m);
            std::cout << p << " ";
            m = m << 1;
        }
        
    }

    return 0;
}