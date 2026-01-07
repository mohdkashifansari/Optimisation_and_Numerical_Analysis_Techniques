#include <iostream>
#include <iomanip>

#include "lu_decomposition.h"
#include "matrix_assembly.h"
#include "cuthill_mckee.h"
#include "bfs.h"
#include "symmetric_permutation.h"
#include "nnz.h"

void print(std::vector<size_t>& v) {
  for (std::vector<size_t>::iterator j = v.begin(); j != v.end(); ++j) {
    std::cout << *j << " ";
  }
  std::cout << std::endl;
}

void print(std::vector<std::vector<double> >& A) {
  for (std::vector<std::vector<double> >::iterator i = A.begin(); i != A.end(); ++i) {
    for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
      std::cout << std::fixed << std::setprecision(4) << std::right << std::setw(7) << std::setfill(' ') << *j << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  size_t n;
  std::cout << "Input dimension: ";
  std::cin >> n;
  std::vector<std::vector<double> > A(n, std::vector<double>(n));
  assembleA(A);

  std::cout << "nnz = " << countNNZ(A) << std::endl;

  std::vector<size_t> permutation(n);
  bfs(A, permutation, n-1);

  // symmetricPermutation(A, permutation);

  // print(permutation);

  // print(A);

  std::vector<size_t> p(n);
  for (size_t i = 0; i < n; i++) p[i] = i;

  luDecomposition(A, p);

  std::cout << "nnz = " << countNNZ(A) << std::endl;

  // print(A);

  // print(p);

  return 0;
}
