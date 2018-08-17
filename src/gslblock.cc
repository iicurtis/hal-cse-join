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

#include "gslblock.h"

gsl_matrix* buildgsl(const size_t& n, const size_t& d, std::vector<std::vector<double>> D) {
  gsl_matrix *A = gsl_matrix_calloc(n*d, n*d);
  for (int i{0}; i<n*d; ++i) {
    for (int j{0}; j<n*d; ++j) {
      gsl_matrix_set(A, i, j, 0);
    }
  }
  for (int i{0}; i<n*n; ++i) {
    size_t x = (i * d) % (n*d);
    size_t y = ((i * d) / (n*d)) * d;
    for (int j{0}; j<d; ++j) {
      gsl_matrix_set(A, x+j, y+j, D[i][j]);
    }
  }
  return A;
}

void gslprint(gsl_matrix* A) {
  for (size_t i{0}; i< A->size1; ++i) {
    for (size_t j{0}; j < A->size2; ++j) {
      fmt::print("{:4.1f} ", gsl_matrix_get(A, i, j));
    }
    fmt::print("\n");
  }
}

gsl_matrix* gslmatmul(gsl_matrix* A, gsl_matrix* B) {
  gsl_matrix* C = gsl_matrix_alloc(A->size1, A->size2);
  gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, A, B, 0.0, C);
  return C;
}
