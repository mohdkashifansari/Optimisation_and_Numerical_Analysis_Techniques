#include <chrono>
#include <iostream>

void matvec(size_t n, double* A, double* x, double* y) {
  for (size_t i = 0; i < n; i++) {
    y[i] = 0;
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      y[i] += A[i * n + j] * x[j];
    }
  }
}

void matvec_bad(size_t n, double* A, double* x, double* y) {
  for (size_t i = 0; i < n; i++) {
    y[i] = 0;
  }
  for (size_t j = 0; j < n; j++) {
    for (size_t i = 0; i < n; i++) {
      y[i] += A[i * n + j] * x[j];
    }
  }
}

int main(int argc, char** argv) {
  size_t n;
  std::cout << "Input dimension: " << std::endl;
  std::cin >> n;
  double* A = new double[n * n];
  double* y = new double[n];
  double* x = new double[n];

  for (size_t i = 0; i < n; i++) {
    x[i] = 1.0;
    for (size_t j = 0; j < n; j++) {
      A[i * n + j] = i;
    }
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> begin, end;

  begin = std::chrono::high_resolution_clock::now();
  matvec(n, A, x, y);
  end = std::chrono::high_resolution_clock::now();

  std::cout << "Time consumed: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
            << std::endl;

  begin = std::chrono::high_resolution_clock::now();
  matvec_bad(n, A, x, y);
  end = std::chrono::high_resolution_clock::now();

  std::cout << "Time consumed: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
            << std::endl;

  delete[] A;
  delete[] x;
  delete[] y;

  return 0;
}
