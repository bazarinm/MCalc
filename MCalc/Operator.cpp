#include "Operator.h"
#include <vector>
#include <string>
#include <exception>
#include <cstddef>

namespace Operator {

	Matrix plus(const Matrix& left, const Matrix& right) {
		if (left.getSize() != right.getSize())
			throw std::exception("Matrix dimensions must agree");

		Matrix sum = left;
		for (std::size_t i = 0; i < left.getSize().rows; ++i)
			for (std::size_t j = 0; i < left.getSize().columns; ++j)
				sum.at(i, j) += right.at(i, j);

		return sum;
	}

	Matrix product(const Matrix& left, const Matrix& right) {
		if (left.getSize().columns != right.getSize().rows)
			throw std::exception("Matrices' dimensions do not agree");

		Matrix product(
			{ left.getSize().rows, right.getSize().columns },
			std::vector<double>(left.getSize().rows * right.getSize().columns, 0)
		);

		for (std::size_t i = 0; i < left.getSize().rows; ++i)
			for (std::size_t j = 0; j < right.getSize().columns; ++j)
				for (std::size_t k = 0; k < left.getSize().columns; ++k)
					product.at(i, j) += left.at(i, k) * right.at(k, j);

		return product;
	}

	Matrix& swapRows(Matrix& matrix, std::size_t row_1, std::size_t row_2) {
		for (std::size_t i = 0; i < matrix.getSize().columns; ++i) {
			double temp = matrix.at(row_1, i);
			matrix.at(row_1, i) = matrix.at(row_2, i);
			matrix.at(row_2, i) = temp;
		}

		return matrix;
	}

	double determinant(Matrix matrix) {
		double det = 1;

		Dimension size = matrix.getSize();
		std::vector<double> temp;

		for (std::size_t i = 0; i < size.rows; ++i) {
			std::size_t k = i;
			for (std::size_t j = i + 1; j < size.columns; ++j)
				if (abs(matrix.at(j, i)) > abs(matrix.at(k, i))) k = j;

			if (abs(matrix.at(k, i)) < ERROR) {
				det = 0;
				break;
			}

			swapRows(matrix, k, i);

			if (i != k) det *= -1;

			det *= matrix.at(i, i);

			for (std::size_t j = i + 1; j < size.columns; ++j)
				matrix.at(i, j) /= matrix.at(i, i);

			for (std::size_t j = 0; j < size.columns; ++j)
				if (j != i && abs(matrix.at(j, i)) > ERROR)
					for (std::size_t k = i + 1; k < size.columns; ++k)
						matrix.at(j, k) -= matrix.at(i, k) * matrix.at(j, i);
		}

		return det;
	}

	Matrix inverse(const Matrix& matrix) {
		double temp = 0;

		Dimension size = matrix.getSize();
		std::vector<double> augmented_entries = matrix.getEntries();
		Matrix inverse(IDENTITY, size.rows);
		augmented_entries.insert(
			std::end(augmented_entries),
			std::begin(inverse.getEntries()),
			std::end(inverse.getEntries())
		);
		Matrix augmented(
			{ size.rows * 2, size.columns },
			augmented_entries
		);

		/*for (std::size_t i = size.rows; i > 1; --i)
			if (augmented.at(i - 1, 1) < augmented.at(i, 1))
				for (std::size_t j = 0; j < augmented.getSize().rows; ++j) {
					temp = augmented_entries[i][j];
					augmented_entries[i][j] = augmented_entries[i - 1][j];
					augmented_entries[i - 1][j] = temp;
				}

		for (std::size_t i = 0; i < _size.rows; ++i)
			for (std::size_t j = 0; j < augm_entr_size; ++j)
				if (j != i) {
					temp = augmented_entries[j][i] / augmented_entries[i][i];
					for (std::size_t k = 0; k < augm_entr_size; ++k)
						augmented_entries[j][k] -= augmented_entries[i][k] * temp;
				}

		for (std::size_t i = 0; i < _size.rows; ++i) {
			temp = augmented_entries[i][i];
			for (std::size_t j = 0; j < augm_entr_size; ++j)
				augmented_entries[i][j] = augmented_entries[i][j] / temp;
		}

		for (std::size_t i = 0; i < _size.rows; ++i) {
			for (std::size_t j = 0; j < _size.rows; ++j)
				inverse_entries[i][j] = augmented_entries[i][j + _size.rows];
			std::cout << std::endl;
		}

		return inverse_entries;
	*/

		return inverse;
	}

}