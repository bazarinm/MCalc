#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>



class Matrix {
public:
    enum SquareTypes {
        UPPER_TRIANGLE, LOWER_TRIANGLE,
        SYMMETRIC, DIAGONAL
    };

    enum RectangleTypes {
        FULL
    };

    enum PredefinedSquareTypes {
        IDENTITY
    };

    enum PredefinedRectangleTypes {
        ZERO, RANDOM
    };

    struct Dimensions {
        std::size_t rows;
        std::size_t columns;

        bool operator==(const Dimensions& other) const {
            return rows == other.rows && columns == other.columns;
        }
        bool operator!=(const Dimensions& other) const {
            return !(*this == other);
        }
    };

    //CONSTRUCTORS
    Matrix();
    Matrix(std::size_t size);
    Matrix(std::size_t rows, std::size_t columns);
    Matrix(std::size_t rows, std::size_t columns, const std::vector<double>& entries);
    Matrix(const std::vector<std::vector<double>>& entries);

    Matrix(RectangleTypes type, std::size_t rows, std::size_t columns, const std::vector<double>& entries);
    Matrix(SquareTypes type, std::size_t size, const std::vector<double>& entries);
    Matrix(PredefinedSquareTypes type, std::size_t size);
    Matrix(PredefinedRectangleTypes type, std::size_t rows, std::size_t columns);

    Matrix(const Matrix& other) = default; //copy

    //AUX
    void display() const; //temporary

    //GETTERS
    Dimensions getSize() const;
    std::vector<double> getEntries() const;
    Matrix getRow(std::size_t) const;
    Matrix getColumn(std::size_t) const;
    double& at(std::size_t row, std::size_t column);
    double at(std::size_t row, std::size_t column) const;

    //OPERATORS
    Matrix operator+(const Matrix& other) const; //sum of 2 matrices
    Matrix operator-(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    Matrix operator*(const Matrix& other) const; //product of 2 matrices
    Matrix operator^(int power) const; 
    Matrix operator/(const Matrix& other) const; //multiplication by an inverse of other matrix
    Matrix& operator*=(const Matrix& other);
    Matrix& operator/=(const Matrix& other);

    Matrix operator*(double scalar) const; //multiplication by a scalar
    Matrix operator/(double scalar) const;
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

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