#include <iostream>
#include <vector>

void assemble(std::vector<std::vector<double>> &A)
{
    size_t n = A.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i == 0 || j == 0 || i == j)
                A[i][j] = 1.0;
            else
                A[i][j] = 0.0;
        }
    }
}
