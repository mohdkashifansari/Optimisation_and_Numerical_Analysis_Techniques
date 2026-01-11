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

  size_t get_nrows();
  size_t get_ncols();

 protected:
  size_t nrows, ncols;
};

class DenseMatrix : public Matrix {
 public:
  DenseMatrix(size_t m, size_t n);
  ~DenseMatrix();
  double& at(size_t i, size_t j);
  std::vector<double> operator*(const std::vector<double>& x);
  void clear();

 private:
  double* data;
};

#endif
