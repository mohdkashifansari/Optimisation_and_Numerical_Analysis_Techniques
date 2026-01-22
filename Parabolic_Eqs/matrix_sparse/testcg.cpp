#include <iostream>
#include <vector>

#include "matrix.h"
#include "matrix_assembly.h"
#include "cg.h"

int main() {

  // ===============================
  // Test 1: SparseMatrix (Poisson)
  // ===============================
  std::cout << "CG test with SparseMatrix (Poisson L_h)\n";

  size_t n = 5;
  SparseMatrix L(n*n, n*n);
  assembleLh(L, n);

  std::vector<double> b(n*n, 1.0);

  std::vector<double> x = conjugate_gradient(L, b);

  std::cout << "Solution x:\n";
  for (size_t i = 0; i < x.size(); ++i)
    std::cout << x[i] << " ";
  std::cout << "\n\n";


  // ===============================
  // Test 2: DenseMatrix
  // ===============================
  std::cout << "CG test with DenseMatrix\n";

  DenseMatrix D(3, 3);
  D(0,0) = 4; D(0,1) = 1; D(0,2) = 0;
  D(1,0) = 1; D(1,1) = 3; D(1,2) = 1;
  D(2,0) = 0; D(2,1) = 1; D(2,2) = 2;

  std::vector<double> b2 = {1, 2, 3};

  std::vector<double> x2 = conjugate_gradient(D, b2);

  std::cout << "Solution x:\n";
  for (size_t i = 0; i < x2.size(); ++i)
    std::cout << x2[i] << " ";
  std::cout << std::endl;

  return 0;
}
