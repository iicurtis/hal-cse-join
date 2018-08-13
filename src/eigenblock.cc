#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <random>
#include <algorithm>
#include "fmt/printf.h"

typedef Eigen::SparseMatrix<double> SpMat;
typedef Eigen::Triplet<double> T;

std::vector<std::vector<double>> generatediags(const size_t n, const size_t d) {
  std::vector<std::vector<double>> A;

  std::random_device rnd;
  std::mt19937 mersenne_engine{rnd()};
  std::uniform_real_distribution<double> unif(0.0, 512.0);
  auto gen = bind(unif, std::ref(rnd));

  auto getrands = [&gen](std::vector<double>& x, size_t num){
    std::generate_n(std::back_inserter(x), num, std::ref(gen));
  };

  for (int i{0}; i<n*n; ++i) {
    std::vector<double> vs;
    getrands(vs, d);
    A.emplace_back(vs);
  }
  return A;
}

SpMat buildsparse(const size_t& n, const size_t& d, std::vector<std::vector<double>>& D) {
  std::vector<T> coefficients;
  for (int i{0}; i<n*n; ++i) {
    size_t x = (i * d) % (n*d);
    size_t y = ((i * d) / (n*d)) * d;
    for (int j{0}; j<d; ++j) {
      // fmt::print("X: {}  Y: {}  d: {}\n", x+j, y+j, d);
      coefficients.emplace_back(T(x+j, y+j, D[i][j]));
    }
  }
  SpMat A(n*d, n*d);
  A.setFromTriplets(coefficients.begin(), coefficients.end());
  return A;
}

int main() {
  const size_t n = 6;
  const size_t d = 8;
  std::vector<std::vector<double>> D = generatediags(n, d);
  SpMat A = buildsparse(n, d, D);
  const Eigen::IOFormat CleanFmt(3, 0, " ", "\n", "|", "|");
  std::cout << Eigen::MatrixXd(A).format(CleanFmt) << std::endl;
}
