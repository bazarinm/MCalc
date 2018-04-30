#include "Operator.h"

#include "Function.h"
#include "Variable.h"
#include <vector>

Operator::Operator(std::string name) : Token(OPERATOR), _function(Function(name)) {}

Variable Operator::invoke(std::vector<Variable> v) {
    return _function(v);
}