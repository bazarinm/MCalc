#include "Matrix.h"
#include "Operator.h"
#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>
#include <string>

//AUX
void Matrix::display() const {
	for (std::size_t i = 0; i < _size.rows; ++i) {
		for(std::size_t j = 0; j < _size.columns; ++j)
			std::cout << at(i, j) << " ";
		std::cout << std::endl;
	}
}

//CONSTRUCTORS
Matrix::Matrix(std::vector<std::vector<double>> entries) {
	if (entries.size() == 0)
		throw std::exception("The initializer matrix is empty");

	_size.rows = entries.size();
	_size.columns = entries[0].size();
	for (std::vector<double>& row : entries) {
		if (row.size() != _size.columns)
			throw std::exception("The initializer matrix is not of a rectangular shape");

		for (double entry : row)
			_entries.push_back(entry);
	}
}

Matrix::Matrix(Dimension size, std::vector<double> entries) : _size(size) {
	if (entries.size() != (size.rows * size.columns))
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
			_entries[i * _size.rows + i] = entries[i];

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
			_entries[i * _size.rows + i] = 1;

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
	return _entries[row * _size.rows + column];
}

double Matrix::at(std::size_t row, std::size_t column) const {
	return _entries[row * _size.rows + column];
}

//OPERATORS
Matrix Matrix::operator+(const Matrix& other) const { //sum of 2 matrices
	return Operator::plus(*this, other);
}

Matrix& Matrix::operator+=(const Matrix& other) {
	return *this = Operator::plus(*this, other);
}

Matrix Matrix::operator*(const Matrix& other) const { //product of 2 matrices
	return Operator::product(*this, other);
}

Matrix Matrix::operator/(const Matrix& other) const {
	return Operator::product(*this, other.inverse());
}

double Matrix::determinant() const {
	return Operator::determinant(*this);
}

Matrix Matrix::inverse() const {
	return Operator::inverse(*this);
}