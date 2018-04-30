#include "Function.h"

#include <string>
#include <vector>
#include <map>
#include <exception>

Function::Function(const std::string& name) : _name(name)
{
    //DATABASE GOES HERE:

    if (name == "det") {
        _arity = 1;
        _priority = 1;
        _associativity = RIGHT;

        _arguments[{ Variable::MATRIX }] = true; 

        _function[{ Variable::MATRIX }] = [](std::vector<Variable> args) -> Variable {
            return args[0].matrix().determinant();
        };
    }
    else if (name == "+") {
        _arity = 2;
        _priority = 1;
        _associativity = BOTH;

        _arguments[{ Variable::MATRIX, Variable::MATRIX }] = true;
        _arguments[{ Variable::SCALAR, Variable::SCALAR }] = true;

        _function[{ Variable::MATRIX, Variable::MATRIX }] = [](std::vector<Variable> args) -> Variable {
            return args[0].matrix() + args[1].matrix();
        };
        _function[{ Variable::SCALAR, Variable::SCALAR }] = [](std::vector<Variable> args) -> Variable {
            return args[0].scalar() + args[1].scalar();
        };
    }
    else if (name == "*") {
        _arity = 2;
        _priority = 2;
        _associativity = BOTH;

        _arguments[{ Variable::MATRIX, Variable::MATRIX }] = true;
        _arguments[{ Variable::SCALAR, Variable::SCALAR }] = true;
        _arguments[{ Variable::MATRIX, Variable::SCALAR }] = true;
        _arguments[{ Variable::SCALAR, Variable::MATRIX }] = true;

        _function[{ Variable::MATRIX, Variable::MATRIX }] = [](std::vector<Variable> args) -> Variable {
            return args[0].matrix() * args[1].matrix();
        };
        _function[{ Variable::SCALAR, Variable::SCALAR }] = [](std::vector<Variable> args) -> Variable {
            return args[0].scalar() * args[1].scalar();
        };
        _function[{ Variable::MATRIX, Variable::SCALAR }] = [](std::vector<Variable> args) -> Variable {
            return args[0].matrix() * args[1].scalar();
        };
        _function[{ Variable::SCALAR, Variable::MATRIX }] = [](std::vector<Variable> args) -> Variable {
            return args[1].matrix() * args[0].scalar();
        };
    }

    //AND SO ON. ANY NEW FUNCTION MUST BE DESCRIBED HERE.
}

Variable Function::operator()(std::vector<Variable> arguments) {
    std::vector<Variable::Type> argument_types;
    for (Variable& argument : arguments)
        argument_types.push_back(argument.getType());

    if (!_arguments[argument_types])
        throw std::exception("Wrong arguments"); 

    return _function[argument_types](arguments);
}

std::string Function::getName() const {
    return _name;
}

unsigned Function::getArity() const {
    return _arity;
}

unsigned Function::getPriority() const {
    return _priority;
}

bool Function::isLeftAssociative() const {
    return _associativity != RIGHT;
}

bool Function::isRightAssociative() const {
    return _associativity != LEFT;
}

bool Function::isOperator() const {
    return _invocation == OPERATOR;
}



