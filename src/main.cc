// DiagBlock
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

#include<iostream>
#include<chrono>
#include "eigenblock.h"
#include "fmt/printf.h"

typedef std::vector<std::vector<double>> DiagMat;

auto timing = [](auto && F, auto && ... params)
{
  auto start = std::chrono::high_resolution_clock::now();
  std::forward<decltype(F)>(F)
    (std::forward<decltype(params)>(params)...); // execute the function
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start).count();
};

int main() {
  fmt::print("Initializing...    ");
  const size_t n = 2048;
  const size_t d = 64;
  fmt::print("n: {}  d: {}\n\n", n, d);
  fmt::print("Generating initial blocks.\n");
  DiagMat D1 = generatediags(n, d);
  DiagMat D2 = generatediags(n, d);

  // Eigen Sparse
  fmt::print("Building Eigen Sparse Matrix.\n");
  SpMat A1 = buildsparse(n, d, D1);
  SpMat A2 = buildsparse(n, d, D2);
  // const Eigen::IOFormat CleanFmt(3, 0, " ", "\n", "|", "|");
  // std::cout << Eigen::MatrixXd(A).format(CleanFmt) << std::endl;
  auto timetaken = timing(eigenspmatmul, A1, A2);
  fmt::print("Time: {} milliseconds", timetaken);
  // TODO: @icurtis - implement element operators (add, sub, mult, div, map)
  //  and transpose, dot (inner product), LU decomp, eigen

  // print: memory consumed
  // matrix inverse

  // Eigen Dense

  // Blaze
  // Personal
}
