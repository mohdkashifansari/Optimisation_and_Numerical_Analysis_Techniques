#include <iostream>

#include "matrix.h"
#include "matrix_assembly.h"

int main() {
  DenseMatrix A(2, 2);
  A(0, 0) = 1.0;
  A.print();

  std::cout << std::endl;

  SparseMatrix B(2, 2, 4);
  B(1, 1) = 2.0 + B(1, 1);
  B.print();

  assembleLh(B, 3);
  B.print();

  std::cout << B.nnz() << std::endl;
}
