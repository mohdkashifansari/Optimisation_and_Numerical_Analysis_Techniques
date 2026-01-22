#ifndef CG_H
#define CG_H

#include <vector>
#include <cmath>
#include "matrix.h"

std::vector<double> conjugate_gradient(
    Matrix& A,
    const std::vector<double>& b,
    size_t max_iter = 1000,
    double tol = 1e-8
) {
  size_t n = b.size();

  std::vector<double> x(n, 0.0);   // initial guess x = 0
  std::vector<double> r = b;       // r = b - A*x = b
  std::vector<double> p = r;

  double rsold = 0.0;
  for (size_t i = 0; i < n; ++i)
    rsold += r[i] * r[i];

  for (size_t iter = 0; iter < max_iter; ++iter) {
    std::vector<double> Ap = A * p;

    double alpha_num = rsold;
    double alpha_den = 0.0;
    for (size_t i = 0; i < n; ++i)
      alpha_den += p[i] * Ap[i];

    double alpha = alpha_num / alpha_den;

    for (size_t i = 0; i < n; ++i)
      x[i] += alpha * p[i];

    for (size_t i = 0; i < n; ++i)
      r[i] -= alpha * Ap[i];

    double rsnew = 0.0;
    for (size_t i = 0; i < n; ++i)
      rsnew += r[i] * r[i];

    if (std::sqrt(rsnew) < tol)
      break;

    double beta = rsnew / rsold;

    for (size_t i = 0; i < n; ++i)
      p[i] = r[i] + beta * p[i];

    rsold = rsnew;
  }

  return x;
}

#endif
