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

  SparseMatrix C(2, 2, 4);
  assembleLh(C, 3);
  C.print();

  std::cout << C.nnz() << std::endl;

  std::cout << "\nproduct test\n";

  std::vector<double> x(B.get_ncols(), 1.0);

  std::vector<double> y = B * x;

  for (size_t i = 0; i < y.size(); ++i)
  std::cout << y[i] << " ";

  std::cout << std::endl;

}
