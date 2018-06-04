#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>

class Matrix {
public:
    enum class SquareTypes {
        UPPER_TRIANGLE, LOWER_TRIANGLE,
        SYMMETRIC, DIAGONAL
    };
    enum class RectangleTypes {
        FULL
    };
    enum class PredefinedSquareTypes {
        IDENTITY
    };
    enum class PredefinedRectangleTypes {
        ZERO, RANDOM
    };

    struct Dimensions {
        std::size_t rows;
        std::size_t columns;

        bool operator==(const Dimensions&) const;
        bool operator!=(const Dimensions&) const;
    };

public:
    Matrix();
    Matrix(std::size_t);
    Matrix(std::size_t rows, std::size_t columns);
    Matrix(std::size_t rows, std::size_t columns, const std::vector<double>& entries);
    Matrix(const std::vector<std::vector<double>>& entries);

    //Matrix(RectangleTypes type, std::size_t rows, std::size_t columns, const std::vector<double>& entries);
    Matrix(SquareTypes, std::size_t, const std::vector<double>& entries);
    Matrix(PredefinedSquareTypes, std::size_t);
    Matrix(PredefinedRectangleTypes, std::size_t rows, std::size_t columns);

    const Dimensions& getSize() const;
    const std::vector<double>& getEntries() const;
    Matrix getRow(std::size_t) const;
    Matrix getColumn(std::size_t) const;
    double& at(std::size_t row, std::size_t column);
    double at(std::size_t row, std::size_t column) const;

    Matrix operator+(const Matrix&) const; //sum of 2 matrices
    Matrix operator-(const Matrix&) const;
    Matrix& operator+=(const Matrix&);
    //Matrix& operator-=(const Matrix& other);

    Matrix operator*(const Matrix&) const; //product of 2 matrices
    Matrix operator^(int power) const; 
    Matrix operator/(const Matrix&) const; //multiplication by an inverse of other matrix
    Matrix& operator*=(const Matrix&);
    //Matrix& operator/=(const Matrix& other);

    Matrix operator*(double scalar) const; //multiplication by a scalar
    Matrix operator/(double scalar) const;
    Matrix& operator*=(double scalar);
    //Matrix& operator/=(double scalar);

    Matrix& operator=(const Matrix& other) = default;

    double determinant() const;
    Matrix inverse() const; 
    Matrix transpose() const; 
	Matrix least_squares(int exponent) const;

private:
    Dimensions _size;
    std::vector<double> _entries;

    void swapRows(std::size_t row_1, std::size_t row_2);
};

#endif