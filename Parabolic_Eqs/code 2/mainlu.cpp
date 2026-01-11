#include <iostream>
#include <vector>
#include <iomanip>

#include "lu_decomposition.h"
#include "cuthill_mckee.h"
#include "symmetricPermutation16.h"

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
    const size_t n = 4;

    //std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));

     std::vector<std::vector<double>> A = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1} 
    };

 
    // for (size_t i = 0; i < n; i++) {
    //     for (size_t j = 0; j < n; j++) {
    //         if (i == 0 || j == 0 || i == j) {
    //             A[i][j] = 1.0;
    //         }
    //     }
    // }

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; i++) {
        p[i] = i;
    }
    size_t root = 0;
    cuthill_mckee(A, p, root);
    symmetricPermutation(A, p);

    // print A and p

    print(A);
    print(p);

    return 0;
}
