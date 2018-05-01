#ifndef VARIABLE_H 
#define VARIABLE_H

#include "Matrix.h"
#include <map>

class Variable {
public:
    enum Type { MATRIX, SCALAR, VOID };

    Variable();
    Variable(Matrix&);
    Variable(double);
    Variable(const std::string&);

    Type getType() const;
    Matrix& matrix();
    double& scalar();

    static bool isVariable(const std::string&);
    static void newVariable(const std::string& name, const Variable&);
private:
    Type _type;
    Matrix _matrix;
    double _scalar;

    static std::map<std::string, Variable> _variables;
};

#endif
