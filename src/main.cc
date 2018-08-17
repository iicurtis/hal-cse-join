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

#define LOGGING false

#include<iostream>
#include<chrono>
#include "diagblock.h"
#include "eigenblock.h"
#include "gslblock.h"
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
  const size_t n = 128;
  const size_t d = 16;
  fmt::print("n: {}  d: {}\n\n", n, d);
  fmt::print("Generating initial blocks.\n");
  DiagMat D1 = generatediags(n, d);
  DiagMat D2 = generatediags(n, d);
  fmt::print("Done. Matrix size: {}.\n", n*n*d*d);

  // Eigen Sparse
  {
  fmt::print("\n===EIGEN SPARSE===\n");
  fmt::print("  Building Eigen Sparse Matrix...");
  SpMat spA1 = buildsparse(n, d, D1);
  SpMat spA2 = buildsparse(n, d, D2);
  fmt::print(" Done.\n");
  auto timetaken = timing(eigenspmatmul, spA1, spA2);
  fmt::print("  Matmul: {: 8d} milliseconds\n", timetaken);
  // TODO: @icurtis - implement element operators (add, sub, mult, div, map)
  //  and transpose, dot (inner product), LU decomp, eigen
  // print: memory consumed
  // matrix inverse
  }

  // Eigen Dense
  {
  fmt::print("\n===EIGEN DENSE====\n");
  fmt::print("  Building Eigen Dense Matrix...");
  EMat dA1 = builddense(n, d, D1);
  EMat dA2 = builddense(n, d, D2);
  fmt::print(" Done.\n");
  auto timetaken = timing(eigendmatmul, dA1, dA2);
  fmt::print("  Matmul: {: 8d} milliseconds\n", timetaken);
  if (LOGGING) {
    EMat B = dA1 * dA2;
    const Eigen::IOFormat CleanFmt(3, 0, " ", "\n", "|", "|");
    std::cout << B.format(CleanFmt) << std::endl;
  }
  }

  // Blaze

  // GSL
  {
  fmt::print("\n===GSL DENSE======\n");
  fmt::print("  Building GSL Dense Matrix...");
  gsl_matrix* dA1 = buildgsl(n, d, D1);
  gsl_matrix* dA2 = buildgsl(n, d, D2);
  fmt::print(" Done.\n");
  auto timetaken = timing(gslmatmul, dA1, dA2);
  fmt::print("  Matmul: {: 8d} milliseconds\n", timetaken);
  if (LOGGING) {
    gsl_matrix* B = gslmatmul(dA1, dA2);
    gslprint(B);
  }
  }

  // Personal
  {
  fmt::print("\n===DiagBlock ======\n");
  fmt::print("  Building DiagBlock Dense Matrix...");
  DiagBlock dA1(D1);
  DiagBlock dA2(D2);
  fmt::print(" Done.\n");
  auto timetaken = timing(diagmatmul, dA1, dA2);
  fmt::print("  Matmul: {: 8d} milliseconds\n", timetaken);
  if (LOGGING) {
    DiagBlock B = diagmatmul(dA1, dA2);
    B.print();
  }
  }
}
