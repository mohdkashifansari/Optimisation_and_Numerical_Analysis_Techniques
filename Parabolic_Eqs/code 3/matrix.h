#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
 public:
  Matrix(size_t m, size_t n);
  virtual double& at(size_t i, size_t j) = 0;
  double& operator()(size_t i, size_t j) { return at(i, j); }
  virtual std::vector<double> operator*(const std::vector<double>& x) = 0;
  void print();
  virtual void clear() = 0;
  virtual void reserve(size_t) {};

  // void print();
  size_t get_nrows();
  size_t get_ncols();

 protected:
  size_t nrows, ncols;
};

class DenseMatrix : public Matrix {
 public:
  DenseMatrix(size_t m, size_t n) : Matrix(m, n) {
    data = new double[nrows * ncols];
    for (size_t i = 0; i < ncols * nrows; ++i) {
      data[i] = 0.0;
    }
  };
  ~DenseMatrix();
  double& at(size_t i, size_t j);
  std::vector<double> operator*(const std::vector<double>& x);
  void clear();

 private:
  double* data;
};

class SparseMatrix : public Matrix {
 public:
  SparseMatrix(size_t m, size_t n) : Matrix(m, n){};
  SparseMatrix(size_t m, size_t n, size_t c) : Matrix(m, n) {
    reserve(c);
  }

  double& at(size_t i, size_t j);
  size_t nnz();
  std::vector<double> operator*(const std::vector<double>& x);
  void reserve(size_t);
  void clear();

 private:
  std::vector<size_t> I, J;
  std::vector<double> A;
};
#endif
