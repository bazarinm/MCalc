#include "Variable.h"
#include "Matrix.h"
#include <map>

std::map<std::string, Variable> Variable::_variables;

Variable::Variable() : _type(VOID), _name(constant_name) {}

Variable::Variable(const Matrix& matrix) : _type(MATRIX), _matrix(matrix), _name(constant_name) {}

Variable::Variable(double scalar) : _type(SCALAR), _scalar(scalar), _name(constant_name) {}

Variable::Variable(const std::string& name) {
    auto search = _variables.find(name);
    if (search != _variables.end())
        *this = search->second;
    else {
        _name = name;
        _type = VOID;
        assign(name, *this);
    }
}

Variable::Types Variable::getType() const {
    return _type;
}

Matrix Variable::getMatrix() const {
    if (_type == MATRIX)
        return _matrix;
    else
        throw std::runtime_error("variable: " + _name + " is not a matrix ");
}

std::string Variable::getName() const {
    return _name;
}

double Variable::getScalar() const {
    if (_type == SCALAR)
        return _scalar;
    else
        throw std::runtime_error("variable: " + _name + " is not a matrix ");
}

bool Variable::isExpressionResult() const
{
    return _name == constant_name;
}

bool Variable::isVariable(const std::string& name) {
    bool result = false;

    auto search = _variables.find(name);
    if (search != _variables.end())
        result = true;

    return result;
}

//void Variable::initialize(const std::string& name, const Variable& v) {
//    auto search = _variables.find(name);
//    if (search != _variables.end())
//        throw std::runtime_error("This variable already exists");
//    else
//        _variables[name] = v;
//}

Variable Variable::assign(const std::string& name, const Variable& v) {
    if (name == constant_name)
        throw std::runtime_error("variable: can't assign value to an expression ");

    Variable assignment = v;
    assignment._name = name;
    return _variables[name] = assignment;
}