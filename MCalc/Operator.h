#ifndef OPERATOR_H
#define OPERATOR_H

#include "Matrix.h"
#include <cstddef>

namespace Operator {

	const double ERROR = 1E-9;

	Matrix plus(const Matrix& left, const Matrix& right);
	Matrix minus(const Matrix& left, const Matrix& right);

	Matrix product(const Matrix& left, const Matrix& right);
	Matrix product(double scalar);

	Matrix& swapRows(Matrix&, std::size_t row_1, std::size_t row_2);

	double determinant(Matrix);
	Matrix inverse(const Matrix&);

}

#endif // !OPERATOR_H

