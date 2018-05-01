#include "Operand.h"

#include "Variable.h"
#include <string>

Operand::Operand(const Variable& variable) : Token(OPERAND), _variable(variable) {}

Operand::Operand(const std::string& name) : Token(OPERAND, name), _variable(Variable(name)) {};


Variable Operand::getVariable() const {
    return _variable;
}
