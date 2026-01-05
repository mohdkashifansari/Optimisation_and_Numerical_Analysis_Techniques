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

void printMatrix(const std::vector<std::vector<double>> &A)
{
    for (const auto &row : A) {
        for (double value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    std::vector<std::vector<double>> A = {
        {1, 2, 3},
        {2, 4, 5},
        {3, 5, 6}
    };

    std::vector<size_t> perm = {2, 0, 1};

    std::cout << "Original matrix:\n";
    printMatrix(A);

    symmetricPermutation(A, perm);

    std::cout << "\nAfter symmetric permutation:\n";
    printMatrix(A);

    return 0;
}
