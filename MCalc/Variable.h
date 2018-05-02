#ifndef VARIABLE_H 
#define VARIABLE_H

#include "Matrix.h"
#include <map>

const std::string constant_name = "";

class Variable {
public:
    enum Type { MATRIX, SCALAR, VOID };

    Variable();
    Variable(const Matrix&);
    Variable(double);
    Variable(const std::string&);

    Type getType() const;
    std::string getName() const;
    Matrix getMatrix() const;
    double getScalar() const;
    bool isExpressionResult() const;

    //static void initialize(const std::string& name, const Variable&);
    static Variable assign(const std::string& name, const Variable&);

    static bool isVariable(const std::string&);
private:
    Type _type;
    std::string _name;
    Matrix _matrix;
    double _scalar;

    static std::map<std::string, Variable> _variables;
};

#endif
