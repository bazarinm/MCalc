#include "Function.h"

#include "Database.h"
#include <string>
#include <vector>
#include <map>
#include <exception>

Function::Function(const std::string& name) : _name(name) {
    /*if (name == "det") {
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
    else
        throw std::runtime_error("Not a function");*/

    auto search = database.find(name);
    if (search != database.end()) {
        FunctionInfo entry = search->second;
        _arity = entry._arity;
        _priority = entry._priority;
        _invocation = entry._invocation;
        _associativity = entry._associativity;
        for (std::pair<ArgumentTypesVector, FunctionBody> function : entry._function) 
            _function[function.first] = function.second;
    }
    else
        throw std::runtime_error("No such function");
}

Variable Function::operator()(const std::vector<Variable>& arguments) {
    ArgumentTypesVector argument_types;
    for (const Variable& argument : arguments)
        argument_types.push_back(argument.getType());

    auto search = _function.find(argument_types);
    if (search != _function.end()) 
        return search->second(arguments);
    else
        throw std::runtime_error("Wrong arguments");
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

bool Function::isOperator(const std::string& name) {
    auto search = database.find(name);
    if (search != database.end())
        return search->second._invocation == FunctionInfo::OPERATOR;
    else
        return false;
}

bool Function::isFunction(const std::string& name) {
    auto search = database.find(name);
    if (search != database.end())
        return search->second._invocation == FunctionInfo::FUNCTION;
    else
        return false;
}

bool Function::isLeftAssociative() const {
    return _associativity != FunctionInfo::RIGHT;
}

bool Function::isRightAssociative() const {
    return _associativity != FunctionInfo::LEFT;
}

bool Function::isOperator() const {
    return _invocation == FunctionInfo::OPERATOR;
}



