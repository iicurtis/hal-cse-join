// HAL
// Copyright (C) 2018  Isaac Curtis

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <algorithm>
#include <random>
#include "fmt/printf.h"
#include "eigenblock.h"


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

Eigen::MatrixXd builddense(const size_t& n, const size_t& d, std::vector<std::vector<double>>& D) {
  std::vector<T> coefficients;
  for (int i{0}; i<n*n; ++i) {
    size_t x = (i * d) % (n*d);
    size_t y = ((i * d) / (n*d)) * d;
    for (int j{0}; j<d; ++j) {
      // fmt::print("X: {}  Y: {}  d: {}\n", x+j, y+j, d);
      coefficients.emplace_back(T(x+j, y+j, D[i][j]));
    }
  }
  SpMat Asp(n*d, n*d);
  Asp.setFromTriplets(coefficients.begin(), coefficients.end());
  Eigen::MatrixXd Ad(Asp);
  return Ad;
}

SpMat eigenspmatmul(SpMat& A, SpMat& B) {
  return A * B;
}
