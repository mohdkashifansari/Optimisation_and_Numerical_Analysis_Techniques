#include <iostream>
#include <iomanip>

#include "lu_decomposition.h"
#include "matrix_assembly.h"
#include "cuthill_mckee.h"
#include "bfs.h"
#include "symmetricPermutation16.h"
#include "nnz.h"

void print(std::vector<size_t>& v) {
  for (std::vector<size_t>::iterator j = v.begin(); j != v.end(); ++j) {
    std::cout << *j << " ";
  }
  std::cout << std::endl;
}

void print(std::vector<std::vector<double> >& A) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
  size_t n;
  std::cout << "Input dimension: ";
  std::cin >> n;
  std::vector<std::vector<double> > A(n, std::vector<double>(n));
  //assembleA(A);

  std::cout << "nnz = " << countNNZ(A) << std::endl;

  std::vector<size_t> permutation(n);
  bfs(A, permutation, n-1);

  std::cout << "BFS permutation:" << std::endl;
  print(permutation);

  // symmetricPermutation(A, permutation);

  // print(permutation);

  // print(A);

  //std::vector<size_t> p(n);
  //for (size_t i = 0; i < n; i++) p[i] = i;

  //luDecomposition(A, p);

  //std::cout << "nnz = " << countNNZ(A) << std::endl;

  // print(A);

  // print(p);

  return 0;
}
