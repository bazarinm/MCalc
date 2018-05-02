#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>

enum SquareTypes {
    UPPER_TRIANGLE, LOWER_TRIANGLE,
    SYMMETRIC, DIAGONAL
};

enum RectangleTypes {
    FULL
};

enum PredefinedTypes {
    IDENTITY, ZERO
};

struct Dimension {
    std::size_t _rows;
    std::size_t _columns;

    bool operator==(const Dimension& other) const {
        return _rows == other._rows && _columns == other._columns;
    }
    bool operator!=(const Dimension& other) const {
        return !(*this == other);
    }
};

class Matrix {
public:
    //CONSTRUCTORS
    Matrix();
    Matrix(std::size_t size);
    Matrix(Dimension size, std::vector<double> entries);
    Matrix(std::vector<std::vector<double>> entries);

    Matrix(RectangleTypes type, Dimension size, std::vector<double> entries);
    Matrix(SquareTypes type, std::size_t size, std::vector<double> entries);
    Matrix(PredefinedTypes type, std::size_t size);

    Matrix(const Matrix& other) = default; //copy

    //AUX
    void display() const; //temporary

    //GETTERS
    Dimension getSize() const;
    std::vector<double> getEntries() const;
    double& at(std::size_t row, std::size_t column);
    double at(std::size_t row, std::size_t column) const;

    //OPERATORS
    Matrix operator+(const Matrix& other) const; //sum or residual of 2 matrices
    Matrix operator-(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    Matrix operator*(const Matrix& other) const; //product of 2 matrices
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
private:
    Dimension _size;
    std::vector<double> _entries;

    void swapRows(std::size_t row_1, std::size_t row_2);
};

#endif