//#include <omp.h>
#include <chrono>
#include <iostream>

bool checkPrime(size_t n) {
  for (size_t j = 2; j <= n / 2; ++j)
    if (n % j == 0) return false;
  return true;
}

int main() {
  size_t N = 300'000;
  size_t total = 0;
  
  std::chrono::time_point<std::chrono::high_resolution_clock> begin, end;
  begin = std::chrono::high_resolution_clock::now();

  //double t1 = omp_get_wtime();

  #pragma omp parallel for schedule(dynamic)
// #pragma omp parallel for schedule(static)
  for (size_t n = 2; n <= N; ++n) {
    bool isPrime = checkPrime(n);

    #pragma omp critical
    total = total + (size_t)isPrime;
  }

  //double t2 = omp_get_wtime();

  end = std::chrono::high_resolution_clock::now();

  std::cout << "There are " << total << " primes smaller than " << N << std::endl;
  std::cout << "Time consumed: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
            << std::endl;
}
