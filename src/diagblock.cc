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

#include <cmath>
#include <vector>
#include "fmt/printf.h"
#include "diagblock.h"


DiagBlock::DiagBlock(size_t n, size_t d) : n(n), d(d) {
  for (size_t x{0}; x<d; ++x) {
    gsl_matrix *vs = gsl_matrix_alloc(n, n);
    for (int i{0}; i<n; ++i) {
      for (int j{0}; j<n; ++j) {
        gsl_matrix_set(vs, i, j, 0);
      }
    }
    m.emplace_back(vs);
  }
}

DiagBlock::DiagBlock(std::vector<std::vector<double>> D) {
  n = std::sqrt(D.size());
  d = D[0].size();
  for (size_t x{0}; x<d; ++x) {
    gsl_matrix* vs = gsl_matrix_alloc(n, n);
    for (size_t i{0}; i<n; ++i) {
      for (size_t j{0}; j<n; ++j) {
        gsl_matrix_set(vs, i, j, D[i+j*n][x]);
      }
    }
    m.emplace_back(vs);
  }
}

void DiagBlock::set(size_t r, size_t c, double v) {
  gsl_matrix_set(m[r%d], (r/d), c/d, v);
}

void DiagBlock::setD(size_t i, size_t j, size_t x, double v) {
  gsl_matrix_set(m[x], i, j, v);
}

double DiagBlock::get(size_t r, size_t c) const {
  if (r % d == c % d) {
    return gsl_matrix_get(m[r%d], r/d, c/d);
  }
  else
    return 0.0;
}

double DiagBlock::getD(size_t i, size_t j, size_t x) const {
  return gsl_matrix_get(m[x], i, j);
}

DiagBlock DiagBlock::mul(DiagBlock& other) {
  DiagBlock out(n, d);
  for (size_t x{0}; x<d; ++x) {
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, m[x], other.m[x], 0.0, out.m[x]);
  }
  return out;
}

void DiagBlock::print() {
  for (int i{0}; i<n*d; ++i) {
    for (int j{0}; j<n*d; ++j) {
      if (j % d == i % d) {
        fmt::print("{:04.1f} ", get(i, j));
      } else {
        fmt::print("{:4.0f} ", 0.0);
      }
    }
    fmt::print("\n");
  }
}


DiagBlock diagmatmul(DiagBlock& A, DiagBlock& B) {
  return A.mul(B);
}
