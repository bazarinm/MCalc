#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <exception>
#include <iostream>
#include <string>

const double ERROR = 1E-9;

enum SquareTypes {
	UPPER_TRIANGLE, LOWER_TRIANGLE,
	SYMMETRIC, DIAGONAL
};

enum RectangleTypes {
	FULL
};

struct Dimension {
	std::size_t rows;
	std::size_t columns;

	bool operator==(const Dimension& other) const {
		return rows == other.rows && columns == other.columns;
	}
	bool operator!=(const Dimension& other) const {
		return !(*this == other);
	}
};

template <typename T>
class Matrix {
public:
	//CONSTRUCTORS
	Matrix(Dimension size, std::vector<T> entries);
	Matrix(std::vector<std::vector<T>> entries);

	Matrix(Dimension size, RectangleTypes type);
	Matrix(std::size_t size, SquareTypes type);

	Matrix(const Matrix& other); //copy

								 //AUX
	class Proxy { //for double indexing
	public:
		Proxy(const std::vector<T>& row) : _row(const_cast<std::vector<T>&>(row)) {}
		T& operator[](std::size_t index) {
			return _row[index];
		}
		T operator[](std::size_t index) const {
			return _row[index];
		}
	private:
		std::vector<T>& _row;
	};
	void display() const; //temporary

						  //GETTERS
	Dimension getSize() const;
	Proxy operator[](std::size_t row);
	const Proxy operator[](std::size_t row) const;

	//OPERATORS
	Matrix operator+(const Matrix& other) const; //sum or residual of 2 matrices
	Matrix operator-(const Matrix& other) const;
	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);

	Matrix operator*(const Matrix& other) const; //product of 2 matrices
	Matrix operator/(const Matrix& other) const; //multiplication by an inverse of other matrix
	Matrix& operator*=(const Matrix& other);
	Matrix& operator/=(const Matrix& other);

	Matrix operator*(T scalar) const; //multiplication by a scalar
	Matrix operator/(T scalar) const;
	Matrix& operator*=(T scalar);
	Matrix& operator/=(T scalar);

	Matrix& operator=(const Matrix& other) = default;

	T determinant() const;
	Matrix inverse() const;
private:
	Dimension _size;
	std::vector<std::vector<T>> _entries;
};

//AUX
template <typename T>
void Matrix<T>::display() const {
	for (const std::vector<T>& row : _entries) {
		for (T entry : row)
			std::cout << entry << " ";
		std::cout << std::endl;
	}
}

//CONSTRUCTORS
template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> entries) : _entries(entries) {
	if (entries.size() == 0)
		throw std::exception("initializer matrix is empty");

	_size.rows = _entries.size();
	_size.columns = _entries[0].size();
	for (std::vector<T>& row : _entries)
		if (row.size() != _size.columns)
			throw std::exception("initializer matrix is not of a rectangular shape");
}

template <typename T>
Matrix<T>::Matrix(Dimension size, std::vector<T> entries) : _size(size) {
	_entries = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns));

	std::size_t i = 0;
	for (std::vector<T>& row : _entries)
		for (T& entry : row) {
			entry = entries[i];
			++i;
		}
}

//GETTERS
template <typename T>
typename Matrix<T>::Proxy Matrix<T>::operator[](std::size_t row) {
	return Proxy(_entries[row]);
}

template <typename T>
typename const Matrix<T>::Proxy Matrix<T>::operator[](std::size_t row) const {
	return Proxy(_entries[row]);
}

template <typename T>
Dimension Matrix<T>::getSize() const {
	return _size;
}

//OPERATORS
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const { //sum of 2 matrices
	if (_size != other._size)
		throw std::exception("Matrix dimensions must agree");

	std::vector<std::vector<T>> sum_entries = _entries;
	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; i < _size.columns; ++j)
			sum_entries[i][j] += other[i][j];

	return Matrix<T>(sum_entries);
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
	if (_size != other._size)
		throw std::exception("Matrix dimensions must agree");

	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; i < _size.columns; ++j)
			_entries[i][j] += other[i][j];

	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const { //product of 2 matrices
	if (_size.columns != other._size.rows)
		throw std::exception("Dimensions do not agree");

	std::vector<std::vector<T>> product_entries(
		_size.rows,
		std::vector<T>(other._size.columns, 0)
	);

	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; j < other._size.columns; ++j)
			for (std::size_t k = 0; k < _size.columns; ++k)
				product_entries[i][j] += ((*this)[i][k] * other[k][j]);

	return Matrix<T>(product_entries);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& other) const {
	return (*this) * other.inverse();
}

template<>
double Matrix<double>::determinant() const {
	double det = 1;

	std::vector<std::vector<double>> entries_copy = _entries;
	std::vector<double> temp;

	for (std::size_t i = 0; i < _size.rows; ++i) {
		std::size_t k = i;
		for (std::size_t j = i + 1; j < _size.columns; ++j)
			if (abs(entries_copy[j][i]) > abs(entries_copy[k][i])) k = j;

		if (abs(entries_copy[k][i]) < ERROR) {
			det = 0;
			break;
		}

		temp = entries_copy[i];
		entries_copy[i] = entries_copy[k];
		entries_copy[k] = temp;

		if (i != k) det *= -1;

		det *= entries_copy[i][i];

		for (std::size_t j = i + 1; j < _size.columns; ++j)
			entries_copy[i][j] /= entries_copy[i][i];

		for (std::size_t j = 0; j < _size.columns; ++j)
			if (j != i && abs(entries_copy[j][i]) > ERROR)
				for (std::size_t k = i + 1; k < _size.columns; ++k)
					entries_copy[j][k] -= entries_copy[i][k] * entries_copy[j][i];
	}

	return det;
}

template <typename T>
Matrix<T> Matrix<T>::inverse() const {
	double temp = 0;

	std::vector<std::vector<double>> inverse_entries;
	std::size_t augm_entr_size = _size.rows + _size.rows;
	std::vector<std::vector<double>> augmented_entries = _entries;

	inverse_entries.resize(_size.rows, std::vector<double>(_size.rows));

	augmented_entries.resize(augm_entr_size);
	for (std::size_t i = 0; i < augm_entr_size; ++i)
		augmented_entries[i].resize(augm_entr_size);

	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; j < augm_entr_size; ++j)
			if (j == (i + _size.rows))
				augmented_entries[i][j] = 1;

	for (std::size_t i = _size.rows; i > 1; --i)
		if (augmented_entries[i - 1][1] < augmented_entries[i][1])
			for (std::size_t j = 0; j < augm_entr_size; ++j) {
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
}

#endif