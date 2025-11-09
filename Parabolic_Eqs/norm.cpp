#include <cmath>
#include <iomanip>
#include <iostream>

float version1(float* x, size_t n) {
  float t = 0.0;
  for (size_t i = 0; i < n; i++) {
    t += x[i] * x[i];
  }
  return std::sqrt(t);
}

float version2(float* x, size_t n) {
  float t = 0.0;
  float s = 1.0;
  for (size_t i = 0; i < n; i++) {
    if (std::abs(x[i]) > 0.0) {
      if (std::abs(x[i]) > t) {
        const float k = t / x[i];
        s = 1.0 + s * k * k;
        t = std::abs(x[i]);
      } else {
        const float k = x[i] / t;
        s += k * k;
      }
    }
  }
  return t * std::sqrt(s);
}

int main(int argc, char** argv) {
  size_t n = 1;
  std::cout << "Number of elements: ";
  std::cin >> n;
  float* x = new float[n];
  for (size_t i = 0; i < n; i++) {
    x[i] = 1.0 * i * i;
  }
  float v1 = version1(x, n);
  float v2 = version2(x, n);
  std::cout.precision(20);
  std::cout << std::scientific << "v1 = " << v1 << ", v2 = " << v2 << std::endl;
  std::cout << "Difference = " << std::abs(v1 - v2) << std::endl;
  delete[] x;
}