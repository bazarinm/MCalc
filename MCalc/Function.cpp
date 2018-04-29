#include "Function.h"

#include "Operator.h"
#include <string>
#include <exception>

Function::Function(std::string name)
{
    if (name == "det") {
        _arity = 1;
        _priority = 0;
        _argument_types = { Variable::MATRIX }; 
        _function = [](std::vector<Variable&> args) -> Variable {
            return Operator::determinant(args[0].getMatrix());
        };
    }
    else if (name == "+") {
        _arity = 2;
        _priority = 0;
        _argument_types = { Variable::MATRIX, Variable::MATRIX };
        _function = [](std::vector<Variable&> args) -> Variable {
            return Operator::plus(args[0].getMatrix(), args[1].getMatrix());
        };
    }

    //AND SO ON. ANY NEW FUNCTION MUST BE DESCRIBED HERE.
}

Variable Function::operator()(std::vector<Variable&> args) const {
    if (args.size() != _arity)
        throw std::exception("A wrong number of parameters");

    unsigned counter = 0;
    for (Variable& arg : args) {
        if (arg.getType() != _argument_types[counter++])
            throw std::exception("A wrong parameter");
    }

    _function(args);
}


