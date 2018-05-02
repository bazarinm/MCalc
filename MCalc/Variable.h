#ifndef VARIABLE_H 
#define VARIABLE_H

#include "Matrix.h"
#include <map>

class Variable {
public:
    enum Type { MATRIX, SCALAR, VOID };

    Variable();
    Variable(const Matrix&);
    Variable(double);
    Variable(const std::string&);

    Type getType() const;
    Matrix getMatrix() const;
    double getScalar() const;

    //static void initialize(const std::string& name, const Variable&);
    static void assign(const std::string& name, const Variable&);

    static bool isVariable(const std::string&);
private:
    Type _type;
    Matrix _matrix;
    double _scalar;

    static std::map<std::string, Variable> _variables;
};

#endif
