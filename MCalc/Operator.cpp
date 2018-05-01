#include "Operator.h"

#include "Function.h"
#include "Variable.h"
#include <vector>

Operator::Operator(const std::string& name) : Token(OPERATOR), invoke(Function(name)) {}
