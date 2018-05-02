#include "Variable.h"
#include "Matrix.h"
#include <map>

std::map<std::string, Variable> Variable::_variables;

Variable::Variable() : _type(VOID) {}

Variable::Variable(const Matrix& matrix) : _type(MATRIX), _matrix(matrix) {}

Variable::Variable(double scalar) : _type(SCALAR), _scalar(scalar) {}

Variable::Variable(const std::string& name) : _name(name) {
    if (isVariable(name))
        *this = _variables[name];
    else
        _type = VOID;
}

Variable::Type Variable::getType() const {
    return _type;
}

Matrix Variable::getMatrix() const {
    if (_type == MATRIX)
        return _matrix;
    else
        throw std::runtime_error("Variable is not a matrix");
}

std::string Variable::getName() const {
    return _name;
}

double Variable::getScalar() const {
    if (_type == SCALAR)
        return _scalar;
    else
        throw std::runtime_error("Variable is not a scalar");
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
    //auto search = _variables.find(name);
    //if (search == _variables.end())
    //    throw std::runtime_error("This variable does not exist");
    //else
    //    _variables[name] = v;

    _variables[name] = v;
    _variables[name]._name = name;
    return _variables[name];
}