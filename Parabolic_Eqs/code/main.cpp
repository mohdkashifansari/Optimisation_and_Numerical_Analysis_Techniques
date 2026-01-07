#include <iostream>

#include "lu_decomposition.h"
#include "matrix_assembly.h"
#include "bfs.h"
#include "symmetric_permutation.h"

void printMatrix(std::vector<std::vector<double> >& A) {
  for (std::vector<std::vector<double> >::iterator i = A.begin(); i != A.end(); ++i) {
    for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
      std::cout.width(6); std::cout << *j << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  size_t n;
  std::cout << "Input dimension: ";
  std::cin >> n;
  std::vector<std::vector<double> > A(n, std::vector<double>(n));
  assembleA(A);

  std::vector<size_t> permutation(n);
  bfs(A, permutation,n-1);

  symmetricPermutation(A, permutation);

  for (std::vector<size_t>::iterator i = permutation.begin(); i != permutation.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;

  printMatrix(A);

  std::vector<size_t> p(n);
  for (size_t i = 0; i < n; i++) p[i] = i;

  luDecomposition(A, p);

  printMatrix(A);

  for (std::vector<size_t>::iterator i = p.begin(); i != p.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;

  return 0;
}
