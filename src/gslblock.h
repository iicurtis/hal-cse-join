/*******************************************************************
DiagBlock
Copyright (C) 2018  Isaac Curtis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*******************************************************************/


#ifndef GSLBLOCK_H_UBYY57TR
#define GSLBLOCK_H_UBYY57TR

#include<gsl/gsl_blas.h>
#include<vector>
#include "fmt/printf.h"

gsl_matrix* buildgsl(const size_t& n, const size_t& d, std::vector<std::vector<double>> D);
void gslprint(gsl_matrix* A);
gsl_matrix* gslmatmul(gsl_matrix* A, gsl_matrix* B);

#endif /* end of include guard: GSLBLOCK_H_UBYY57TR */
