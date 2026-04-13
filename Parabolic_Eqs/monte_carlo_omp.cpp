#include <cmath>
#include <iostream>
#include <random>
#include <sstream>
#include <omp.h>

int main(int argc, char** argv) {
  size_t N = 10'000'000;
  size_t d = 2;

  std::stringstream strstr;
  if (argc > 1) {
    strstr << argv[1];
    strstr >> N;
  }
  if (argc > 2) {
    strstr << argv[2];
    strstr >> d;
  }

  // Exact volume of the d-dimensional unit ball
  const double exact_vol = pow(M_PI, 0.5 * d) / tgamma(0.5 * d + 1.0);

  size_t T = omp_get_max_threads();
  if (N%T != 0) exit(1);
  std::vector<std::minstd_rand> LCGs(T);
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  double box_vol = 2.0;
  for (size_t i = 0; i < d - 1; i++) box_vol *= 2.0;

  std::vector<size_t> hit(T);

  #pragma omp parallel num_threads(T)
  {
    size_t t = omp_get_thread_num();
    LCGs[t].seed(1337);
    LCGs[t].discard(t*N/T);
    for (size_t i = 0; i < N/T; i++) {
      double norm = 0.0;
      for (size_t j = 0; j < d; j++) {
        const double x = distribution(LCGs[t]);
        norm += x * x;
      }
      if (norm <= 1.0) hit[t]++;
    }
  }
  for (size_t i=1; i<T; ++i) {
    hit[0] += hit[i];
  }

  std::cout << "Monte Carlo volume = " << (box_vol * hit[0]) / N << std::endl;
  std::cout << "Volume             = " << exact_vol << std::endl;

  return 0;
}