#include <iostream>

#include "matrix.h"
#include "matrix_assembly.h"
#include "cg.h"

int main() {

  const size_t n = 2;
  SparseMatrix A(2,2);
  A(0,0) = 2.0; A(0,1) = 1.0;
  A(1,0) = 1.0; A(1,1) = 3.0;

  //SparseMatrix B(2, 2, 4);
  //assembleLh(B, 2);
  A.print();

  std::vector<double> b(n, 2.0);
  std::vector<double> x(n);
  CGSolve(A, x, b);
  for(auto it=x.begin(); it != x.end(); ++it)
    std::cout << *it << "\n";


  //CGSolve(B, x, b);
  //for(auto it=x.begin(); it != x.end(); ++it)
  // std::cout << *it << "\n";  
  return 0;
}
