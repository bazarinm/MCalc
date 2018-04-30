#include "Operand.h"

#include "Variable.h"

Operand::Operand(Variable variable) : Token(OPERAND), _variable(variable) {}

Variable Operand::getVariable() const {
    return _variable;
}
