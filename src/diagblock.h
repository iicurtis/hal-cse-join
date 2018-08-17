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

#ifndef DIAGBLOCK_H_NX5AWK2N
#define DIAGBLOCK_H_NX5AWK2N

#include<vector>
#include<gsl/gsl_blas.h>

class DiagBlock;


class DiagBlock {
  private:
    size_t n, d;

  // constructors
  public:
    std::vector<gsl_matrix*> m;
    DiagBlock(size_t n, size_t d);
    DiagBlock(std::vector<std::vector<double>> D);

  // accessors
  public:
    void set(size_t r, size_t c, double v); // Get by traditional
    void setD(size_t i, size_t j, size_t x, double v);
    double get(size_t r, size_t c) const; // Get by traditional
    double getD(size_t i, size_t j, size_t x) const ; // Get by Diag block
    // std::vector<double> getblock(size_t i, size_t j); // Get by Diag block

    // operations
    DiagBlock mul(DiagBlock &other);
    DiagBlock inverse();
    void print();
};

DiagBlock diagmatmul(DiagBlock& A, DiagBlock& B);

#endif /* end of include guard: DIAGBLOCK_H_NX5AWK2N */
