void symmetricPermutation(std::vector<std::vector<double> > &A,
                          std::vector<size_t> &permutation) {
  std::vector<std::vector<double> > B(A);
  for (size_t i = 0; i < A.size(); i++) {
    for (size_t j = 0; j < A.size(); j++) {
      std::swap(B[i][j], A[i][permutation[j]]);
    }
  }
  for (size_t i = 0; i < A.size(); i++) {
    for (size_t j = 0; j < A.size(); j++) {
      std::swap(A[i][j], B[permutation[i]][j]);
    }
  }
}
