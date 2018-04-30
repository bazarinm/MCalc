#ifndef VARIABLE_H 
#define VARIABLE_H

#include "Matrix.h"

class Variable {
public:
    enum Type { MATRIX, SCALAR, VOID };

    Variable();
    Variable(Matrix&);
    Variable(double);

    Type getType() const;
    Matrix& matrix();
    double& scalar();

private:
    Type _type;
    Matrix _matrix;
    double _scalar;
};

#endif
