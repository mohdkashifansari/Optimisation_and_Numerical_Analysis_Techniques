#ifndef MATRIX_ASSEMBLY
#define MATRIX_ASSEMBLY

#include <vector>

void assembleA(std::vector<std::vector<double> > &A) {
  for (size_t i = 0; i < A.size(); ++i) {
    A[i][i] = 1.0;
    A[0][i] = 1.0;
    A[i][0] = 1.0;
  }
}

#endif
