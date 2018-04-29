#include "Function.h"

#include "Operator.h"
#include <string>
#include <exception>

Function::Function(std::string name)
{
    if (name == "det") {
        _priority = 0;

        _argument_types[{ Variable::MATRIX }] = true; 

        _function[{ Variable::MATRIX }] = [](std::vector<Variable> args) -> Variable {
            return Operator::determinant(args[0].matrix());
        };
    }
    else if (name == "+") {
        _priority = 0;

        _argument_types[{ Variable::MATRIX, Variable::MATRIX }] = true;
        _argument_types[{ Variable::SCALAR, Variable::SCALAR }] = true;

        _function[{ Variable::MATRIX, Variable::MATRIX }] = [](std::vector<Variable> args) -> Variable {
            return Operator::plus(args[0].matrix(), args[1].matrix());
        };
        _function[{ Variable::SCALAR, Variable::SCALAR }] = [](std::vector<Variable> args) -> Variable {
            return args[0].scalar() + args[1].scalar();
        };
    }

    //AND SO ON. ANY NEW FUNCTION MUST BE DESCRIBED HERE.
}

Variable Function::operator()(std::vector<Variable> args) {
    std::vector<Variable::Type> arg_types;
    for (Variable& arg : args)
        arg_types.push_back(arg.getType());

    if (!_argument_types[arg_types])
        throw std::exception("Wrong arguments"); 

    return _function[arg_types](args);
}


