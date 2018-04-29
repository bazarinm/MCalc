#include "Matrix.h"
#include "Operator.h"
#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>
#include <string>

const double ERROR = 1E-9;

//AUX
void Matrix::display() const {
	for (std::size_t i = 0; i < _size._rows; ++i) {
		for(std::size_t j = 0; j < _size._columns; ++j)
			std::cout << at(i, j) << " ";
		std::cout << std::endl;
	}
}

//CONSTRUCTORS
Matrix::Matrix(std::size_t size) : Matrix(ZERO, size) {}

Matrix::Matrix(std::vector<std::vector<double>> entries) {
	if (entries.size() == 0)
		throw std::exception("The initializer matrix is empty");

	_size._rows = entries.size();
	_size._columns = entries[0].size();
	for (std::vector<double>& row : entries) {
		if (row.size() != _size._columns)
			throw std::exception("The initializer matrix is not of a rectangular shape");

		for (double entry : row)
			_entries.push_back(entry);
	}
}

Matrix::Matrix(Dimension size, std::vector<double> entries) : _size(size) {
	if (entries.size() != (size._rows * size._columns))
		throw std::exception("An unexpected number of elements");
	
	_entries = entries;
}

Matrix::Matrix(SquareTypes type, std::size_t size, std::vector<double> entries) : _size({size, size}) {
	_entries = std::vector<double>(size * size, 0);

	switch (type) {
	case DIAGONAL : 
		if (entries.size() != size)
			throw std::exception("An unexpected number of elements");

		for (std::size_t i = 0; i < size; ++i)
			_entries[i * _size._rows + i] = entries[i];

		break;
	case UPPER_TRIANGLE:
		if (entries.size() != (size * size + size) / 2)
			throw std::exception("An unexpected number of elements");

		std::reverse(entries.begin(), entries.end());
		for (std::size_t i = 0; i < size; ++i)
			for (std::size_t j = i; j < size; ++j) {
				_entries[i * size + j] = entries.back(); 
				entries.pop_back();
			}

		break;
	case LOWER_TRIANGLE:
		if (entries.size() != (size * size + size) / 2)
			throw std::exception("An unexpected number of elements");

		std::reverse(entries.begin(), entries.end());
		for (std::size_t i = 0; i < size; ++i)
			for (std::size_t j = 0; j <= i; ++j) {
				_entries[i * size + j] = entries.back();
				entries.pop_back();
			}

		break;
	case SYMMETRIC:
		if (entries.size() != (size * size + size) / 2)
			throw std::exception("An unexpected number of elements");

		std::reverse(entries.begin(), entries.end());
		for (std::size_t i = 0; i < size; ++i)
			for (std::size_t j = i; j < size; ++j) {
				_entries[i * size + j] = _entries[j *size + i] = entries.back();
				entries.pop_back();
			}

		break;
	}

}

Matrix::Matrix(PredefinedTypes type, std::size_t size): _size({ size, size }) {
	_entries = std::vector<double>(size * size, 0);

	switch (type) {
	case IDENTITY :
		for (std::size_t i = 0; i < size; ++i)
			_entries[i * _size._rows + i] = 1;

		break;
	case ZERO: break;
	}
}


//GETTERS
Dimension Matrix::getSize() const {
	return _size;
}

std::vector<double> Matrix::getEntries() const {
	return _entries;
}

double& Matrix::at(std::size_t row, std::size_t column) {
	return _entries[row * _size._rows + column];
}

double Matrix::at(std::size_t row, std::size_t column) const {
	return _entries[row * _size._rows + column];
}

//OPERATORS
Matrix Matrix::operator+(const Matrix& other) const { //sum of 2 matrices
	if (_size != other.getSize())
		throw std::exception("Matrix dimensions must agree");

	Matrix sum = *this;
	for (std::size_t i = 0; i < _size._rows; ++i)
		for (std::size_t j = 0; j < _size._columns; ++j)
			sum.at(i, j) += other.at(i, j);

	return sum;
}

Matrix& Matrix::operator+=(const Matrix& other) {
	if (getSize() != other.getSize())
		throw std::exception("Matrix dimensions must agree");

	for (std::size_t i = 0; i < getSize()._rows; ++i)
		for (std::size_t j = 0; j < getSize()._columns; ++j)
			at(i, j) += other.at(i, j);

	return *this;
}

Matrix Matrix::operator*(const Matrix& other) const { //product of 2 matrices
	if (getSize()._columns != other.getSize()._rows)
		throw std::exception("Matrices' dimensions do not agree");

	Matrix product(
		{ getSize()._rows, other.getSize()._columns },
		std::vector<double>(getSize()._rows * other.getSize()._columns, 0)
	);

	for (std::size_t i = 0; i < getSize()._rows; ++i)
		for (std::size_t j = 0; j < other.getSize()._columns; ++j)
			for (std::size_t k = 0; k < getSize()._columns; ++k)
				product.at(i, j) += at(i, k) * other.at(k, j);

	return product;
}

Matrix Matrix::operator/(const Matrix& other) const {
	return *this * other.inverse();
}

void Matrix::swapRows(std::size_t row_1, std::size_t row_2) {
	for (std::size_t i = 0; i < getSize()._columns; ++i) {
		double temp = at(row_1, i);
		at(row_1, i) = at(row_2, i);
		at(row_2, i) = temp;
	}
}

double Matrix::determinant() const {
	double det = 1;

	Matrix matrix = *this; //copy
	Dimension size = getSize();
	std::vector<double> temp;

	for (std::size_t i = 0; i < size._rows; ++i) {
		std::size_t k = i;
		for (std::size_t j = i + 1; j < size._columns; ++j)
			if (abs(matrix.at(j, i)) > abs(matrix.at(k, i))) 
				k = j;

		if (abs(matrix.at(k, i)) < ERROR) {
			det = 0;
			break;
		}

		matrix.swapRows(k, i);

		if (i != k) 
			det *= -1;

		det *= matrix.at(i, i);

		for (std::size_t j = i + 1; j < size._columns; ++j)
			matrix.at(i, j) /= matrix.at(i, i);

		for (std::size_t j = 0; j < size._columns; ++j)
			if (j != i && abs(matrix.at(j, i)) > ERROR)
				for (std::size_t k = i + 1; k < size._columns; ++k)
					matrix.at(j, k) -= matrix.at(i, k) * matrix.at(j, i);
	}

	return det;
}

Matrix Matrix::inverse() const {
	Dimension size = getSize();
	Matrix inverse(IDENTITY, size._rows);

	/*std::vector<double> augmented_entries = getEntries();
	augmented_entries.insert(
		std::end(augmented_entries),
		std::begin(inverse.getEntries()),
		std::end(inverse.getEntries())
	);
	Matrix augmented(
		{ size._rows, size._columns * 2},
		augmented_entries
	);	*/

	//WTF??

	return inverse;
}