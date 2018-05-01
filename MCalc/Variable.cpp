#include "Variable.h"
#include "Matrix.h"
#include <map>

std::map<std::string, Variable> Variable::_variables;

Variable::Variable() : _type(VOID) {}

Variable::Variable(const Matrix& matrix) : _type(MATRIX), _matrix(matrix) {}

Variable::Variable(double scalar) : _type(SCALAR), _scalar(scalar) {}

Variable::Variable(const std::string& name) : Variable(_variables[name]) {}

Variable::Type Variable::getType() const {
    return _type;
}

Matrix Variable::getMatrix() const {
    return _matrix;
}

double Variable::getScalar() const {
    return _scalar;
}

bool Variable::isVariable(const std::string& name) {
    bool result = false;

    auto search = _variables.find(name);
    if (search != _variables.end())
        result = true;

    return result;
}

void Variable::newVariable(const std::string& name, const Variable& v) {
    auto search = _variables.find(name);
    if (search != _variables.end())
        throw std::runtime_error("This variable already exists");
    else
        _variables[name] = v;
}