#include "Operator.h"
#include "Matrix.h"

namespace Functions {

	Matrix plus(const Matrix& left, const Matrix& right) {
		return left + right;
	}

	Matrix product(const Matrix& left, const Matrix& right) {
		return left * right;
	}

    Matrix product(const Matrix& left, double right) {
        return left * right;
    }

	double determinant(const Matrix& matrix) {
		return matrix.determinant();
	}

	Matrix inverse(const Matrix& matrix) {
		return matrix.inverse();
	}

}