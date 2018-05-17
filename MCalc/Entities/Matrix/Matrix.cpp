#include "Matrix.h"

#include <algorithm>
#include <vector>
#include <stdexcept>
#include <random>
#include <string>

Matrix::Matrix() : _size({ 0, 0 }), _entries({}) 
{
}

Matrix::Matrix(std::size_t size) : Matrix(PredefinedRectangleTypes::ZERO, size, size)
{
}

Matrix::Matrix(std::size_t rows, std::size_t columns) :
    _size({ rows, columns }),
    _entries(std::vector<double>(_size.columns * _size.rows, 0))
{
}

Matrix::Matrix(const std::vector<std::vector<double>>& entries) 
{
    if (entries.size() == 0)
        throw std::runtime_error("matrix: the initializer matrix is empty ");

    _size.rows = entries.size();
    _size.columns = entries[0].size();
    for (const std::vector<double>& row : entries) {
        if (row.size() != _size.columns)
            throw std::runtime_error("matrix: the initializer matrix is not of a rectangular shape ");

        for (double entry : row)
            _entries.push_back(entry);
    }
}

Matrix::Matrix(std::size_t rows, std::size_t columns, const std::vector<double>& entries) : _size({ rows, columns }) 
{
    if (entries.size() != (_size.rows * _size.columns))
        throw std::runtime_error("matrix: an unexpected number of elements ");
    
    _entries = entries;
}

Matrix::Matrix(SquareTypes type, std::size_t size, const std::vector<double>& entries) : _size({size, size}) 
{
    _entries = std::vector<double>(size * size, 0);

    std::size_t k = 0;
    switch (type) {
    case SquareTypes::DIAGONAL : 
        if (entries.size() != size)
            throw std::runtime_error("matrix: an unexpected number of elements ");

        for (std::size_t i = 0; i < size; ++i)
            _entries[i * _size.rows + i] = entries[i];

        break;
    case SquareTypes::UPPER_TRIANGLE:
        if (entries.size() != (size * size + size) / 2)
            throw std::runtime_error("matrix: an unexpected number of elements ");

        for (std::size_t i = 0; i < size; ++i)
            for (std::size_t j = i; j < size; ++j)
                _entries[i * size + j] = entries[k++]; 

        break;
    case SquareTypes::LOWER_TRIANGLE:
        if (entries.size() != (size * size + size) / 2)
            throw std::runtime_error("matrix: an unexpected number of elements ");

        for (std::size_t i = 0; i < size; ++i)
            for (std::size_t j = 0; j <= i; ++j) 
                _entries[i * size + j] = entries[k++];

        break;
    case SquareTypes::SYMMETRIC:
        if (entries.size() != (size * size + size) / 2)
            throw std::runtime_error("matrix: an unexpected number of elements ");

        for (std::size_t i = 0; i < size; ++i)
            for (std::size_t j = i; j < size; ++j) 
                _entries[i * size + j] = _entries[j *size + i] = entries[k++];

        break;
    }

}

Matrix::Matrix(PredefinedRectangleTypes type, std::size_t rows, std::size_t columns) : _size({ rows, columns }) 
{
    _entries = std::vector<double>(_size.rows * _size.columns, 0);

    std::random_device seed;
    std::default_random_engine rand(seed());
    std::uniform_int_distribution<int> discrete(0, 9);
    switch (type) {
    case PredefinedRectangleTypes::RANDOM:
        for (std::size_t i = 0; i < _size.rows; ++i)
            for (std::size_t j = 0; j < _size.columns; ++j)
                _entries[i * _size.columns + j] = discrete(rand);

        break;
    case PredefinedRectangleTypes::ZERO: break; //already zero
    }
}

Matrix::Matrix(PredefinedSquareTypes type, std::size_t size): _size({ size, size }) 
{
    _entries = std::vector<double>(size * size, 0);

    switch (type) {
    case PredefinedSquareTypes::IDENTITY:
        for (std::size_t i = 0; i < size; ++i)
            _entries[i * _size.columns + i] = 1;

        break;
    }
}


//GETTERS
Matrix::Dimensions Matrix::getSize() const {
    return _size;
}

std::vector<double> Matrix::getEntries() const {
    return _entries;
}

Matrix Matrix::getRow(std::size_t row) const
{
    if (row > _size.rows - 1)
        throw std::runtime_error("matrix: no " + std::to_string(row) + "th row ");

    std::vector<double> row_entries;
    for (std::size_t i = 0; i < _size.columns; ++i)
        row_entries.push_back(at(row, i));

    return Matrix(1, _size.columns, row_entries);
}

Matrix Matrix::getColumn(std::size_t column) const
{
    if (column > _size.columns - 1)
        throw std::runtime_error("matrix: no " + std::to_string(column) + "th column ");

    std::vector<double> column_entries;
    for (std::size_t i = 0; i < _size.rows; ++i)
        column_entries.push_back(at(i, column));

    return Matrix(_size.rows, 1, column_entries);
}

double& Matrix::at(std::size_t row, std::size_t column) 
{
    if (row < _size.rows && column < _size.columns)
        return _entries[row * _size.columns + column];
    else
        throw std::runtime_error("matrix: subscript out of range ");
}

double Matrix::at(std::size_t row, std::size_t column) const 
{
    if (row < _size.rows && column < _size.columns)
        return _entries[row * _size.columns + column];
    else
        throw std::runtime_error("matrix: subscript out of range");
}

//OPERATORS
Matrix Matrix::operator+(const Matrix& other) const 
{ 
    if (_size != other.getSize())
        throw std::runtime_error("matrix: matrices' dimensions must agree ");

    Matrix sum(*this);
    for (std::size_t i = 0; i < _size.rows; ++i)
        for (std::size_t j = 0; j < _size.columns; ++j)
            sum.at(i, j) += other.at(i, j);

    return sum;
}

Matrix Matrix::operator-(const Matrix& other) const {
    return *this + (other * -1);
}

Matrix& Matrix::operator+=(const Matrix& other) 
{
    if (getSize() != other.getSize())
        throw std::runtime_error("matrix: matrices' dimensions must agree ");

    for (std::size_t i = 0; i < getSize().rows; ++i)
        for (std::size_t j = 0; j < getSize().columns; ++j)
            at(i, j) += other.at(i, j);

    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const 
{ 
    if (getSize().columns != other.getSize().rows)
        throw std::runtime_error("matrix: matrices' dimensions must agree ");

    Matrix product(
        getSize().rows, other.getSize().columns,
        std::vector<double>(getSize().rows * other.getSize().columns, 0)
    );

    for (std::size_t i = 0; i < getSize().rows; ++i)
        for (std::size_t j = 0; j < other.getSize().columns; ++j)
            for (std::size_t k = 0; k < getSize().columns; ++k)
                product.at(i, j) += at(i, k) * other.at(k, j);

    return product;
}

Matrix Matrix::operator^(int power) const
{
    if (_size.rows != _size.columns)
        throw std::runtime_error("matrix: matrix must be square ");

    Matrix result;
    if (power == 0)
        result = Matrix(PredefinedSquareTypes::IDENTITY, _size.rows);
    else {
        result = *this;
        bool inverse = false;

        if (power < 0) {
            inverse = true;
            power *= -1;
        }
        for (int i = 1; i < power; ++i) 
            result *= *this;

        if (inverse)
            result = result.inverse();
    }

    return result;
}

Matrix Matrix::operator*(double scalar) const 
{ 
    Matrix product = *this;

    for (std::size_t i = 0; i < getSize().rows; ++i)
        for (std::size_t j = 0; j < getSize().columns; ++j)
            product.at(i, j) *= scalar;

    return product;
}

Matrix Matrix::operator/(double scalar) const
{
    return *this * (1 / scalar);
}

Matrix & Matrix::operator*=(double scalar)
{
    for (std::size_t i = 0; i < getSize().rows; ++i)
        for (std::size_t j = 0; j < getSize().columns; ++j)
            at(i, j) *= scalar;

    return *this;
}

Matrix Matrix::operator/(const Matrix& other) const {
    return *this * other.inverse();
}

Matrix& Matrix::operator*=(const Matrix & other)
{
    if (getSize().columns != other.getSize().rows)
        throw std::runtime_error("matrix: matrices' dimensions must agree ");

    Matrix product(
        getSize().rows, other.getSize().columns,
        std::vector<double>(getSize().rows * other.getSize().columns, 0)
    );

    for (std::size_t i = 0; i < getSize().rows; ++i)
        for (std::size_t j = 0; j < other.getSize().columns; ++j)
            for (std::size_t k = 0; k < getSize().columns; ++k)
                product.at(i, j) += at(i, k) * other.at(k, j);

    return (*this = product);
}

void Matrix::swapRows(std::size_t row_1, std::size_t row_2) 
{
    for (std::size_t i = 0; i < getSize().columns; ++i) {
        double temp = at(row_1, i);
        at(row_1, i) = at(row_2, i);
        at(row_2, i) = temp;
    }
}

double Matrix::determinant() const 
{
    const double ERROR = 1E-9;

    if (_size.columns != _size.rows)
        throw std::runtime_error("matrix: matrix must be square");

    double det = 1;

    Matrix matrix = *this; //copy
    Dimensions size = getSize();
    std::vector<double> temp;

    for (std::size_t i = 0; i < size.rows; ++i) {
        std::size_t k = i;
        for (std::size_t j = i + 1; j < size.columns; ++j)
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

        for (std::size_t j = i + 1; j < size.columns; ++j)
            matrix.at(i, j) /= matrix.at(i, i);

        for (std::size_t j = 0; j < size.columns; ++j)
            if (j != i && abs(matrix.at(j, i)) > ERROR)
                for (std::size_t k = i + 1; k < size.columns; ++k)
                    matrix.at(j, k) -= matrix.at(i, k) * matrix.at(j, i);
    }

    return det;
}

Matrix Matrix::inverse() const 
{
    if (determinant() == 0)
        throw std::runtime_error("matrix: matrix is not invertible ");

	Dimensions size = getSize();

	std::size_t augm_entr_size = _size.rows + _size.columns;

	std::vector<std::vector<double>> inverse_entries(
		_size.rows,
		std::vector<double>(_size.columns)
	);

	std::vector<std::vector<double>> augmented_entries(
		_size.rows,
		std::vector<double>(_size.columns)
	);

	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; j < _size.columns; ++j)
			augmented_entries[i][j] = at(i, j);

	augmented_entries.resize(augm_entr_size);
	for (std::size_t i = 0; i < augm_entr_size; ++i)
		augmented_entries[i].resize(augm_entr_size);

	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; j < augm_entr_size; ++j)
			if (j == (i + _size.rows))
				augmented_entries[i][j] = 1;

	for (std::size_t i = _size.rows; i > 1; --i)
		if (augmented_entries[i - 1][1] < augmented_entries[i][1])
			for (std::size_t j = 0; j < augm_entr_size; ++j) 
				std::swap(
					augmented_entries[i][j], 
					augmented_entries[i - 1][j]
				);

	for (std::size_t i = 0; i < _size.rows; ++i)
		for (std::size_t j = 0; j < augm_entr_size; ++j)
			if (j != i) {
				double temp = augmented_entries[j][i] / augmented_entries[i][i];
				for (std::size_t k = 0; k < augm_entr_size; ++k)
					augmented_entries[j][k] -= augmented_entries[i][k] * temp;
			}

	for (std::size_t i = 0; i < _size.rows; ++i) {
		double temp = augmented_entries[i][i];
		for (std::size_t j = 0; j < augm_entr_size; ++j)
			augmented_entries[i][j] = augmented_entries[i][j] / temp;
	}

	for (std::size_t i = 0; i < _size.rows; ++i) {
		for (std::size_t j = 0; j < _size.rows; ++j)
			inverse_entries[i][j] = augmented_entries[i][j + _size.rows];
	}

	return inverse_entries;
}

Matrix Matrix::transpose() const
{
    Matrix transposed({ _size.columns, _size.rows });

    for (std::size_t i = 0; i < _size.rows; ++i)
        for (std::size_t j = 0; j < _size.columns; ++j)
            transposed.at(j, i) = at(i, j);

    return transposed; 
}

Matrix Matrix::least_squares(int exponent) const 
{
    if (exponent < 0)
        throw std::runtime_error("matrix: exponent must be a positive value");
    if (_size.rows != 2)
        throw std::runtime_error("matrix: input must be of size 2 by x ");

	std::vector<double> a(exponent + 1);
	std::vector<double> b(exponent + 1);

	std::vector<double> x(_size.columns);
	std::vector<double> y(_size.columns);

	for (std::size_t i = 0; i < _size.columns; ++i) {
		x[i] = _entries[i];
		y[i] = _entries[_size.columns + i];
	}

	std::vector<std::vector<double>> sum(
		exponent + 1,
		std::vector<double>(exponent + 1)
	);

	for (int i = 0; i < exponent + 1; ++i)
		for (int j = 0; j < exponent + 1; ++j)
		{
			sum[i][j] = 0;
			for (std::size_t k = 0; k < _size.columns; ++k)
				sum[i][j] += pow(x[k], i + j);
		}

	for (int i = 0; i < exponent + 1; ++i) {
		b[i] = 0;
		for (std::size_t k = 0; k < _size.columns; ++k)
			b[i] += pow(x[k], i) * y[k];
	}

	for (int i = 0; i < exponent; i++) {
		int temp = i;
		for (int j = i + 1; j < exponent + 1; ++j)
			if (fabs(sum[temp][i]) < fabs(sum[j][i])) temp = j;

		for (int k = i; k < exponent + 1; ++k)
			std::swap(sum[temp][k], sum[i][k]);

		std::swap(b[temp], b[i]);

		for (int j = i + 1; j < exponent + 1; ++j) {
			double c = -sum[j][i] / sum[i][i];
			for (int k = i; k < exponent + 1; ++k)
				sum[j][k] = sum[j][k] + c * sum[i][k];
			b[j] = b[j] + c * b[i];
		}
	}

	a[exponent] = b[exponent] / sum[exponent][exponent];

	for (int i = exponent + 1 - 2; i >= 0; --i) {
		for (int k = i + 1; k < exponent + 1; ++k)
			b[i] = b[i] - a[k] * sum[i][k];
		a[i] = b[i] / sum[i][i];
	}

	std::vector<std::vector<double>> coefficients(
		1,
		std::vector<double>(exponent + 1)
	);

	for (int i = 0; i < exponent + 1; ++i)
		coefficients[0][i] = a[i];

	return coefficients;
}

bool Matrix::Dimensions::operator==(const Dimensions& other) const {
    return rows == other.rows && columns == other.columns;
}
bool Matrix::Dimensions::operator!=(const Dimensions& other) const {
    return !(*this == other);
}