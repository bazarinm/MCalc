#ifndef OPERATOR_H
#define OPERATOR_H

#include "Matrix.h"

namespace Operator {

	Matrix plus(const Matrix& left, const Matrix& right);
	Matrix minus(const Matrix& left, const Matrix& right);

	Matrix product(const Matrix& left, const Matrix& right);
	Matrix product(const Matrix& left, double right);

	double determinant(const Matrix&);
	Matrix inverse(const Matrix&);

}

#endif // !OPERATOR_H

