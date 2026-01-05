#include <iostream>
#include <vector>

// Assemble the special matrix
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

// Print a matrix to the console
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
    // Choose matrix size
    size_t n = 5;

    // Create an n x n matrix initialized with zeros
    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));

    // Assemble the matrix
    assemble(A);

    // Print the result
    std::cout << "Assembled matrix:\n";
    printMatrix(A);

    return 0;
}
