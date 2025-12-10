#include <iostream>
#include <vector>

int main(int argc, char** argv) {
  size_t n;
  std::cout << "Input dimension: ";
  std::cin >> n;

  // vectors for the coordinate format
  std::vector<double> aa_coord(5 * n * n - 4 * n);
  std::vector<size_t> jr_coord(5 * n * n - 4 * n);
  std::vector<size_t> jc_coord(5 * n * n - 4 * n);

  size_t j = 0;
  for (size_t row = 0; row < n; ++row) {
    for (size_t col = 0; col < n; ++col) {
      size_t ind = row * n + col;

      if (row > 0) {
        aa_coord[j] = -1.0;
        jr_coord[j] = ind;
        jc_coord[j++] = ind - n;
      }

      if (col > 0) {
        aa_coord[j] = -1.0;
        jr_coord[j] = ind;
        jc_coord[j++] = ind - 1;
      }

      aa_coord[j] = 4.0;
      jr_coord[j] = ind;
      jc_coord[j++] = ind;
      
      if (col < n - 1) {
        aa_coord[j] = -1.0;
        jr_coord[j] = ind;
        jc_coord[j++] = ind + 1;
      }

      if (row < n - 1) {
        aa_coord[j] = -1.0;
        jr_coord[j] = ind;
        jc_coord[j++] = ind + n;
      }
    }
  }

  // storage for the CSR format
  std::vector<double> aa_csr(aa_coord);
  std::vector<size_t> ja_csr(jc_coord);
  std::vector<size_t> ia_csr(n*n+1);
  
  for (size_t i=0; i<n*n; i++) {
    size_t count=0;
    if (i/n > 0) count++;
    if (i%n > 0) count++;
    count++;
    if (i%n < n - 1) count++;
    if (i/n < n - 1) count++;
    ia_csr[i+1] = ia_csr[i] + count;
  }  

  // dense 2d structure
  std::vector< std::vector< double > > m(n*n, std::vector<double>(n*n));
  for (size_t k=0; k<aa_coord.size(); ++k) {
    m[jr_coord[k]][jc_coord[k]] = aa_coord[k];
  }

  for (std::vector< std::vector< double > >::iterator i=m.begin(); i!=m.end(); ++i) {
    for (std::vector<double>::iterator j=i->begin(); j!=i->end(); ++j) {
      std::cout << *j << "\t";
    }
    std::cout << std::endl;
  }

  for (std::vector< double >::iterator i=aa_csr.begin(); i!=aa_csr.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
  for (std::vector< size_t >::iterator i=ja_csr.begin(); i!=ja_csr.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
  for (std::vector< size_t >::iterator i=ia_csr.begin(); i!=ia_csr.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}
