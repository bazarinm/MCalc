#include "Function.h"

#include <string>
#include <vector>
#include <map>
#include <exception>

std::map<std::string, FunctionInfo> Function::_database = {
    {
        "det", 
        {
            1, 2,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[0].getMatrix().determinant(); }
                }
            }
        }
    },

    {
        "*", 
        {
            2, 2,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[0].getMatrix() * args[1].getMatrix(); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](std::vector<Variable> args) -> Variable { return args[0].getScalar() * args[1].getScalar(); }
                },
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](std::vector<Variable> args) -> Variable { return args[0].getMatrix() * args[1].getScalar(); }
                },
                {
                    { Variable::SCALAR, Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[1].getMatrix() * args[0].getScalar(); }
                },
            }
        }
    },

    {
        "+", 
        {
            2, 1,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[0].getMatrix() + args[1].getMatrix(); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](std::vector<Variable> args) -> Variable { return args[0].getScalar() + args[1].getScalar(); }
                },
            }
        }
    }
};

Function::Function(const std::string& name) : _name(name) {
    auto search = _database.find(name);
    if (search != _database.end()) {
        //_function = search->second._function;
    }
    else
        throw std::runtime_error("No such function");
}

Variable Function::operator()(const std::vector<Variable>& arguments) {
    ArgumentTypesVector argument_types;
    for (const Variable& argument : arguments)
        argument_types.push_back(argument.getType());

    auto search = _database[_name]._function.find(argument_types);
    if (search != _database[_name]._function.end())
        return search->second(arguments);
    else
        throw std::runtime_error("Wrong arguments");
}

std::string Function::getName() const {
    return _name;
}

unsigned Function::getArity() const {
    return _database[_name]._arity;
}

unsigned Function::getPriority() const {
    return _database[_name]._priority;
}

bool Function::isOperator(const std::string& name) {
    auto search = _database.find(name);
    if (search != _database.end())
        return search->second._invocation == FunctionInfo::OPERATOR;
    else
        return false;
}

bool Function::isFunction(const std::string& name) {
    auto search = _database.find(name);
    if (search != _database.end())
        return search->second._invocation == FunctionInfo::FUNCTION;
    else
        return false;
}

bool Function::isLeftAssociative() const {
    return _database[_name]._associativity != FunctionInfo::RIGHT;
}

bool Function::isRightAssociative() const {
    return _database[_name]._associativity != FunctionInfo::LEFT;
}

bool Function::isOperator() const {
    return _database[_name]._invocation == FunctionInfo::OPERATOR;
}



