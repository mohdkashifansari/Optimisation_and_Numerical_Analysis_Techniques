#include "matrix.h"

void Matrix::print() {
  for (size_t i = 0; i < nrows; ++i) {
    for (size_t j = 0; j < ncols; ++j) {
      std::cout << at(i, j) << "\t";
    }
    std::cout << std::endl;
  }
}

Matrix::Matrix(size_t m, size_t n) {
  nrows = m;
  ncols = n;
}

size_t Matrix::get_nrows() { return nrows; }
size_t Matrix::get_ncols() { return ncols; }

DenseMatrix::DenseMatrix(size_t m, size_t n) : Matrix(m, n) {
  data = new double[nrows * ncols];
  for (size_t i = 0; i < ncols * nrows; ++i) {
    data[i] = 0.0;
  }
}

DenseMatrix::~DenseMatrix() { delete[] data; }

double& DenseMatrix::at(size_t i, size_t j) { return data[i * ncols + j]; }

void DenseMatrix::clear() {
  for (size_t i = 0; i < nrows * ncols; i++) data[i] = 0.0;
}

std::vector<double> DenseMatrix::operator*(const std::vector<double>& x) {
  std::vector<double> y(nrows);
  for (size_t i = 0; i < nrows; i++)
    for (size_t j = 0; j < ncols; j++) {
      y[i] += at(i, j) * x[j];
    }
  return y;
}
