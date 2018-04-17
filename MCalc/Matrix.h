#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <exception>
#include <string>

enum MatrixTypes {
	UPPER_TRIANGLE, LOWER_TRIANGLE,
	SYMMETRIC, DIAGONAL, FULL
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
	Matrix(std::size_t size, MatrixTypes type);
	Matrix(Dimension size, FULL);
	Matrix(const Matrix& other);
	Matrix(std::vector<std::vector<T>> entries);
	//Matrix(Dimension);
	//Matrix(int, MType);
	//Matrix(std::vector<std::vector<T>>);

	//for double indexing
	class Proxy {
		Proxy(std::vector<T>& row): _row(row) {}
		T& operator[](std::size_t index) {
			return _row[index];
		}
		T operator[](std::size_t index) const {
			return _row[index];
		}
	private:
		std::vector<int>& _row;
	};

	//GETTERS
	Dimension getSize() const;
	Proxy operator[](std::size_t row);
	const Proxy operator[](std::size_t row) const;

	//OPERATORS
	Matrix& operator+(const Matrix& other) const; //sum or residual of 2 matrices
	Matrix& operator-(const Matrix& other) const;
	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);

	Matrix& operator*(const Matrix& other) const; //product of 2 matrices
	Matrix& operator/(const Matrix& other) const; //multiplication by an inverse of other matrix
	Matrix& operator*=(const Matrix& other);
	Matrix& operator/=(const Matrix& other);

	Matrix& operator*(T scalar) const; //multiplication by a scalar
	Matrix& operator/(T scalar) const;
	Matrix& operator*=(T scalar);
	Matrix& operator/=(T scalar);

	Matrix& operator=(const Matrix& other) = default;

	T determinant() const;
	Matrix inverse() const;
private:
	Dimension _size;
	std::vector<std::vector<T>> _entries;
};

//CONSTRUCTORS
template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> entries) : _entries(entries) {
	if (entries.size() == 0)
		throw std::exception("initializer matrix is empty");

	_size.rows = _entries.size();
	_size.columns = _entries[0];
	for (std::vector<T>& row : _entries)
		if (row.size() != _size.columns)
			throw std::exception("initializer matrix is not of a rectangular shape");
}

template <typename T>
Matrix<T>::Matrix(Dimension size, std::vector<T> entries) : _size(size) {
	_entries = std::vector<std::vector<T>>(std::vector<T>(size.columns), size.rows);

	for (std::vector<T>& row : _entries)
		for (T& entry : row)
			entry = entries;
}

//GETTERS
template <typename T>
Matrix<T>::Proxy Matrix<T>::operator[](std::size_t row) {
	return Proxy(entries[row]);
}

template <typename T>
const Matrix<T>::Proxy Matrix<T>::operator[](std::size_t row) const {
	return Proxy(entries[row]);
}

template <typename T>
Dimension Matrix<T>::getSize() const {
	return _size;
}

//OPERATORS
template <typename T> 
Matrix<T>& Matrix<T>::operator+(const Matrix<T>& other) const { //sum of 2 matrices
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
Matrix<T>& Matrix<T>::operator*(const Matrix<T>& other) const { //product of 2 matrices
	if (_size.columns != other._size.rows)
		throw std::exception("Dimensions do not agree");

	std::vector<std::vector<T>> product_entries(
		std::vector<T>(other._size.columns, 0), 
		other._size.rows);

	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; i < _size.columns; ++j)
			for (std::size_t k = 0; k < _size.columns; ++k)
				product_entries[i][j] += *this[i][k] + other[k][j];

	return Matrix<T>(product_entries);
}

template <typename T>
Matrix<T>& Matrix<T>::operator/(const Matrix<T>& other) const { 
	return (*this) * other.inverse();
}
#endif