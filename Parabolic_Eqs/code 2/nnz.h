#ifndef NNZ_H
#define NNZ_H

#include <vector>

size_t countNNZ(std::vector<std::vector<double> >& A) {
  size_t nnz = 0;
  for (std::vector<std::vector<double> >::iterator i = A.begin(); i != A.end(); ++i) {
    for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
      if(std::abs(*j) > 1e-12) nnz++;
    }
  }
  return nnz;
}

#endif