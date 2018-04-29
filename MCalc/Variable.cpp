#include "Variable.h"
#include "Matrix.h"

Variable::Variable(Matrix& matrix) : _type(MATRIX), _matrix(matrix) {}

Variable::Variable(double scalar) : _type(SCALAR), _scalar(scalar) {}

Variable::Type Variable::getType() const {
    return _type;
}

Matrix& Variable::getMatrix() {
    return _matrix;
}

double& Variable::getScalar() {
    return _scalar;
}