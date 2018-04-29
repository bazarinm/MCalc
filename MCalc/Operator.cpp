#include "Operator.h"
#include <vector>
#include <string>
#include <exception>
#include <cstddef>

namespace Operator {

	Matrix plus(const Matrix& left, const Matrix& right) {
		return left + right;
	}

	Matrix product(const Matrix& left, const Matrix& right) {
		left * right;
	}

	double determinant(const Matrix& matrix) {
		return matrix.determinant();
	}

	Matrix inverse(const Matrix& matrix) {
		return matrix.inverse();
	}

}