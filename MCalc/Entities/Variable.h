#ifndef VARIABLE_H 
#define VARIABLE_H

#include "Matrix/Matrix.h"
#include <string>
#include <map>

class Variable {
public:
    enum class Types { MATRIX, SCALAR, VOID };

public:
    Variable();
    Variable(const Matrix&);
    Variable(double);
    Variable(const std::string&);

    Types getType() const;
    const std::string& getName() const;
    const Matrix& getMatrix() const;
    double getScalar() const;
    bool isAssignmentResult() const;

    static const Variable& assign(const std::string&, const Variable&);

    static bool isVariable(const std::string&);
private:
    Types _type;
    std::string _name;
    Matrix _matrix;
    double _scalar;

    const static std::string constant_name;
    static std::map<std::string, Variable> _variables;
};

#endif
