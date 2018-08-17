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
  for (int i{0}; i<n*n; ++i) {
    std::vector<double> vs(d, 0);
    m.emplace_back(vs);
  }
}

DiagBlock::DiagBlock(std::vector<std::vector<double>> D) : m(D) {
  n = std::sqrt(m.size());
  d = m[0].size();
}

void DiagBlock::set(size_t r, size_t c, double v) {
  m[(r/d)+c/d*n][r%d] = v;
}

void DiagBlock::setD(size_t i, size_t j, size_t x, double v) {
  m[i+j*n][x] = v;
}

double DiagBlock::get(size_t r, size_t c) const {
  if (r % d == c % d) {
    return m[(r/d)+c/d*n][r%d];
  }
  else
    return 0.0;
}

double DiagBlock::getD(size_t i, size_t j, size_t x) const {
  return m[i+j*n][x];
}

std::vector<double> DiagBlock::getblock(size_t i, size_t j) {
  return m[i+j*n];
}

DiagBlock DiagBlock::mul(DiagBlock& other) {
  DiagBlock out(n, d);
  for (size_t x{0}; x<d; ++x) {
    for (size_t i{0}; i<n; ++i) {
      for (size_t j{0}; j<n; ++j) {
        double sum = 0;
        for (size_t p{0}; p<n; ++p) {
          sum += getD(i, p, x)*other.getD(p, j, x);
        }
        out.setD(i, j, x, sum);
      }
    }
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
