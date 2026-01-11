#ifndef MATRIX_ASSEMBLY
#define MATRIX_ASSEMBLY

#include <vector>
#include <cmath>

#include "matrix.h"

void assembleA(Matrix& A, size_t N) {
  A.clear();
  A.reserve(3*N);
  for (size_t i = 0; i < N; ++i) {
    A(i,i) = 1.0;
    A(0,i) = 1.0;
    A(i,0) = 1.0;
  }
}

void assembleLh(Matrix& A, size_t n) {
  const size_t N = n*n;
  A.clear();
  A.reserve(5 * n * n - 4 * n);

  const double h = 1.0/(n+1);
  const double hFactor = 1.0/(h*h);
  for (size_t row = 0; row < n; ++row) {
    for (size_t col = 0; col < n; ++col) {
      size_t ind = row * n + col;
      if (row > 0) A(ind,ind - n) = -1.0 * hFactor;
      if (col > 0) A(ind,ind - 1) = -1.0 * hFactor;
      A(ind,ind) = 4.0 * hFactor;
      if (col < n - 1) A(ind,ind + 1) = -1.0 * hFactor;
      if (row < n - 1) A(ind,ind + n) = -1.0 * hFactor;
    }
  }
}

#endif