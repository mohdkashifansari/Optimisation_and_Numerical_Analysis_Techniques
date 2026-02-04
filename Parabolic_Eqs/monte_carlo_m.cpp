#include <cmath>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <fstream>


int main(int argc, char** argv) {
  size_t N = 10'000'000;
  size_t d = 2
  ;

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

  std::mt19937_64 mt(time(0));

  //std::minstd_rand lcg(time(0));

  // std::cout << "mt " << mt() << " lcg " << lcg() << std::endl;

  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  size_t hit = 0;

  std::vector<size_t> n_values;
  std::vector<double> error;

  n_values.reserve(N / 100000 + 1);
  error.reserve(N / 100000 + 1);

  double box_vol = 2.0;
  for (size_t i = 0; i < d - 1; i++) box_vol *= 2.0;

  for (size_t i = 0; i < N; i++) {
    double norm = 0.0;
    for (size_t j = 0; j < d; j++) {
      const double x = distribution(mt);
      // std::cout << x << " ";
      norm += x * x;
    }
    if (norm <= 1.0) hit++;
    if (i % 100000 == 0) {
       double mc_vol = box_vol * (double)(hit) / (double)(i);
       double err = std::abs(mc_vol - exact_vol);

       n_values.push_back(i);
       error.push_back(err);
       std::cout << i << ";" << err << std::endl;
    }
  }
  std::cout << "Monte Carlo volume = " << (box_vol * hit) / N << std::endl;
  std::cout << "Volume             = " << exact_vol << std::endl;

  // export error
  std::ofstream file("mc_error.csv");
  file << "n,error\n";

  for (size_t i = 0; i < error.size(); i++) {
    file << n_values[i] << "," << error[i] << "\n";
  }
  file.close();

  return 0;
}