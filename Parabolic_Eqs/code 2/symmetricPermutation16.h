#include <iostream>
#include <vector>

void symmetricPermutation(std::vector<std::vector<double>> &A,
                          const std::vector<size_t> &perm)
{
    size_t n = A.size();

    std::vector<std::vector<double>> B = A;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            A[i][j] = B[perm[i]][perm[j]];
        }
    }
}
