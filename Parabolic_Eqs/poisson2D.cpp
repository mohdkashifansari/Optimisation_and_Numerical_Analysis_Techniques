#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    int N;
    std::cout << "Input dimension N: ";
    std::cin >> N;


    int n = N * N; 
    //double h = 1.0 / (N + 1.0);
    double diag = 4.0 ;
    double off  = -1.0 ;

    // Dense 
    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));

    // COO: row_idx, col_idx, val
   
    std::vector<int>    coo_row;
    std::vector<int>    coo_col;
    std::vector<double> coo_val;
    coo_row.reserve(5 * n);
    coo_col.reserve(5 * n);
    coo_val.reserve(5 * n);

    // CSR
    std::vector<int>    csr_row_ptr(n + 1, 0);
    std::vector<int>    csr_col_ind;
    std::vector<double> csr_val;
    csr_col_ind.reserve(5 * n);
    csr_val.reserve(5 * n);

    int nnz_count = 0; 

    // Loop over (i,j) 
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            int k = i + j * N; 

            csr_row_ptr[k] = nnz_count;

           
            A[k][k] = diag;

            coo_row.push_back(k);
            coo_col.push_back(k);
            coo_val.push_back(diag);

            csr_col_ind.push_back(k);
            csr_val.push_back(diag);
            ++nnz_count;

            // left (i-1,j)
            if (i > 0) {
                int kl = (i - 1) + j * N;

                A[k][kl] = off;

                coo_row.push_back(k);
                coo_col.push_back(kl);
                coo_val.push_back(off);

                csr_col_ind.push_back(kl);
                csr_val.push_back(off);
                ++nnz_count;
            }

            // right  (i+1,j) 
            if (i < N - 1) {
                int kr = (i + 1) + j * N;

                A[k][kr] = off;

                coo_row.push_back(k);
                coo_col.push_back(kr);
                coo_val.push_back(off);

                csr_col_ind.push_back(kr);
                csr_val.push_back(off);
                ++nnz_count;
            }

            // down (i,j-1)
            if (j > 0) {
                int kd = i + (j - 1) * N;

                A[k][kd] = off;

                coo_row.push_back(k);
                coo_col.push_back(kd);
                coo_val.push_back(off);

                csr_col_ind.push_back(kd);
                csr_val.push_back(off);
                ++nnz_count;
            }

            // up (i,j+1)
            if (j < N - 1) {
                int ku = i + (j + 1) * N;

                A[k][ku] = off;

                coo_row.push_back(k);
                coo_col.push_back(ku);
                coo_val.push_back(off);

                csr_col_ind.push_back(ku);
                csr_val.push_back(off);
                ++nnz_count;
            }

            
        }
    }
    csr_row_ptr[n] = nnz_count; 


    // print
    if (n <= 20) {
        std::cout << "\nDense matrix L_h (size " << n << " x " << n << "):\n";
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c)
                std::cout << std::setw(10) << A[r][c] << " ";
            std::cout << "\n";
        }
    } else {
        std::cout << "\nDense matrix assembled (size " << n << " x " << n
                  << "), not printed (too large).\n";
    }

    std::cout << "\nCOO format (row, col, val):\n";
    for (std::size_t i = 0; i < coo_val.size(); ++i) {
        std::cout << "(" << coo_row[i] << ", " << coo_col[i]
                  << ", " << coo_val[i] << ")\n";
    }

    std::cout << "\nCSR format:\nrow_ptr: ";
    for (int x : csr_row_ptr) std::cout << x << " ";
    std::cout << "\ncol_ind: ";
    for (int x : csr_col_ind) std::cout << x << " ";
    std::cout << "\nvalues:  ";
    for (double v : csr_val) std::cout << v << " ";
    std::cout << "\n";

    return 0;
}
