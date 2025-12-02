#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    int N;
    std::cout << "Number of interior nodes N: ";
    std::cin >> N;

    if (N <= 0) {
        std::cerr << "N must be positive.\n";
        return 1;
    }

    double h = 1.0 / (N + 1.0);
    double diag = 2.0 / (h * h);
    double off  = -1.0 / (h * h);

    // (a) dense matrix 
    std::vector<std::vector<double>> dense(N, std::vector<double>(N, 0.0));
    for (int i = 0; i < N; ++i) {
        dense[i][i] = diag;
        if (i > 0)     dense[i][i - 1] = off;
        if (i < N - 1) dense[i][i + 1] = off;
    }

    // (b) sparse coordinate 
    std::vector<int>    coo_row;
    std::vector<int>    coo_col;
    std::vector<double> coo_val;
    coo_row.reserve(3 * N - 2);
    coo_col.reserve(3 * N - 2);
    coo_val.reserve(3 * N - 2);

    for (int i = 0; i < N; ++i) {
        // left off-diagonal
        if (i > 0) {
            coo_row.push_back(i);
            coo_col.push_back(i - 1);
            coo_val.push_back(off);
        }
        // main diagonal
        coo_row.push_back(i);
        coo_col.push_back(i);
        coo_val.push_back(diag);
        // right off-diagonal
        if (i < N - 1) {
            coo_row.push_back(i);
            coo_col.push_back(i + 1);
            coo_val.push_back(off);
        }
    }

    // (c) CSR format
    int nnz = (N == 1) ? 1 : (3 * N - 2);
    std::vector<int>    csr_row(N + 1);
    std::vector<int>    csr_col_ind(nnz);
    std::vector<double> csr_val(nnz);

    int k = 0;
    csr_row[0] = 0;
    for (int i = 0; i < N; ++i) {
        if (i > 0) {                 // left off-diagonal
            csr_col_ind[k] = i - 1;
            csr_val[k]     = off;
            ++k;
        }
        csr_col_ind[k] = i;          // main diagonal
        csr_val[k]     = diag;
        ++k;
        if (i < N - 1) {             // right off-diagonal
            csr_col_ind[k] = i + 1;
            csr_val[k]     = off;
            ++k;
        }
        csr_row[i + 1] = k;
    }

    // print results

    std::cout << "\nDense matrix L_h:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            std::cout << std::setw(10) << dense[i][j] << " ";
        std::cout << "\n";
    }

    std::cout << "\nCOO format (row, col, val):\n";
    for (std::size_t i = 0; i < coo_val.size(); ++i) {
        std::cout << "(" << coo_row[i] << ", " << coo_col[i]
                  << ", " << coo_val[i] << ")\n";
    }

    std::cout << "\nCSR format:\nrow_ptr: ";
    for (int x : csr_row) std::cout << x << " ";
    std::cout << "\ncol_ind: ";
    for (int x : csr_col_ind) std::cout << x << " ";
    std::cout << "\nvalues:  ";
    for (double x : csr_val) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
