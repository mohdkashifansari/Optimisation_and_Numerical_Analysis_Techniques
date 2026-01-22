#ifndef CG_H
#define CG_H

#include <vector>

#include "matrix.h"

double inner(const std::vector<double>& x, const std::vector<double>& y) {
  double res = 0.0;
  for (size_t i = 0; i < x.size(); i++) {
    res += x[i] * y[i];
  }
  return res;
}

double norm(const std::vector<double>& x) {
  double res = inner(x,x);
  return std::sqrt(res);
}

void CGSolve(Matrix& A, std::vector<double>& x, std::vector<double>& b,
             double epsilon = 1e-12) {
  const size_t n = x.size();
  std::vector<double> r(n);
  std::vector<double> p(n);
  std::vector<double> tmp(n);

  tmp = A * x;
  for (size_t i = 0; i < n; i++) {
    r[i] = b[i] - tmp[i];
    p[i] = r[i];
  }
  size_t k = 0;
  do {
    tmp = A * p;
    const double rTr = inner(r, r);
    double alpha = rTr / inner(tmp, p);
    for (size_t i = 0; i < n; i++) {
      x[i] += alpha * p[i];
      r[i] -= alpha * tmp[i];
    }
    const double beta = inner(r, r) / rTr;
    for (size_t i = 0; i < n; i++) {
      p[i] = r[i] + beta * p[i];
    }
    k++;
    std::cout << "End of iteration " << k << " with norm(r) = " << norm(r) << std::endl;
  } while (norm(r) > epsilon);
}

#endif