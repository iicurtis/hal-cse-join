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

#ifndef EIGENBLOCK_H_E6WDVXQI
#define EIGENBLOCK_H_E6WDVXQI

#include <Eigen/Sparse>
#include <Eigen/Dense>

typedef Eigen::SparseMatrix<double> SpMat;
typedef Eigen::Triplet<double> T;

std::vector<std::vector<double>> generatediags(const size_t n, const size_t d);
SpMat buildsparse(const size_t& n, const size_t& d, std::vector<std::vector<double>>& D);
Eigen::MatrixXd builddense(const size_t& n, const size_t& d, std::vector<std::vector<double>>& D);
SpMat eigenspmatmul(SpMat& A, SpMat& B);



#endif /* end of include guard: EIGENBLOCK_H_E6WDVXQI */
