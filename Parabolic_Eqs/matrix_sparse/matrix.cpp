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

SparseMatrix::SparseMatrix(size_t m, size_t n) : Matrix(m, n) {}
SparseMatrix::SparseMatrix(size_t m, size_t n, size_t c) : Matrix(m, n) { reserve(c); }

double& SparseMatrix::at(size_t i, size_t j) {
  for (size_t k = 0; k < I.size(); k++)
    if (I[k] == i && J[k] == j) return A[k];

  if (!A.empty()) {
    if (A.back() == 0.0) {
      I.back() = i;
      J.back() = j;
      return A.back();
    }
  }

  I.push_back(i);
  J.push_back(j);
  A.push_back(0.0);
  if (i >= nrows) nrows = i + 1;
  if (j >= ncols) ncols = j + 1;

  return A.back();
}

size_t SparseMatrix::nnz() { return A.size(); }

std::vector<double> SparseMatrix::operator*(const std::vector<double>& x) {
  SparseMatrix& M = *this;

  std::vector<double> y(nrows);
  for (size_t i = 0; i < M.A.size(); i++) y[I[i]] += M.A[i] * x[J[i]];

  return y;
}

void SparseMatrix::clear() {
  A.clear();
  I.clear();
  J.clear();
}

void SparseMatrix::reserve(size_t c) {
  I.reserve(c);
  J.reserve(c);
  A.reserve(c);
}
