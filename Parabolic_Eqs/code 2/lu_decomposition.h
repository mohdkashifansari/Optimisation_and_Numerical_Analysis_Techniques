#ifndef LU_DECOMPOSITION
#define LU_DECOMPOSITION

#include <vector>

int luDecomposition(std::vector<std::vector<double> > &A, std::vector<size_t> &p) {
  int d = 1.0;
  const size_t n = A.size();
  for (size_t k = 0; k < n; k++) {
    // Finding the pivot i
    size_t pivot = k;
    double max = std::abs(A[k][k]);
    for (size_t j = k + 1; j < n; j++) {
      if (std::abs(A[j][k]) > max) {
        max = std::abs(A[j][k]);
        pivot = j;
      }
    }
    if (max < 1e-10) {
      std::cout << "Matrix is close to singularity.\n";
      return -1;
    }
    // swap row i and k
    if (pivot != k) {
      d *= -1.0;
      size_t si = p[pivot];
      p[pivot] = p[k];
      p[k] = si;
      for (size_t j = 0; j < n; j++) {
        double sd = A[pivot][j];
        A[pivot][j] = A[k][j];
        A[k][j] = sd;
      }
    }
    // pivoting
    for (size_t i = k + 1; i < n; i++) {
      A[i][k] /= A[k][k];
      for (size_t j = k + 1; j < n; j++) {
        A[i][j] -= A[i][k] * A[k][j];
      }
    }
  }
  return d;
}

#endif