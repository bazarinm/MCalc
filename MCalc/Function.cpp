#include "Function.h"

#include "Variable.h"
#include <map>
#include <string>
#include <vector>
#include <exception>
#include <functional>

std::map<std::string, FunctionInfo> Function::_database = {
    {
        "", //aux
        {
            0, 0,
            FunctionInfo::FUNCTION, FunctionInfo::BOTH,
            {
                {
                    { },
                    [](std::vector<Variable> args) -> Variable { return Variable(); }
                }
            }
        }
    },

    //DATABASE GOES HERE:
    {
        "det", 
        {
            1, 3,
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

    //AND SO ON
};

Function::Function() : _name("") {}

Function::Function(const std::string& name) : _name(name) {
    auto search = _database.find(name);
    if (search == _database.end()) 
        throw std::runtime_error("No such function");
}

Variable Function::operator()(const std::vector<Variable>& arguments) const {
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

FunctionInfo::InvocationType Function::getInvocationType() const
{
    return _database[_name]._invocation;
}

FunctionInfo::AssociativityType Function::getAssociativityType() const
{
    return _database[_name]._associativity;
}

bool Function::isOperator(const std::string& name) {
    bool is_operator = false;

    auto search = _database.find(name);
    if (search != _database.end())
        is_operator = search->second._invocation == FunctionInfo::OPERATOR;

    return is_operator;
}

bool Function::isFunction(const std::string& name) {
    bool is_function = false;

    auto search = _database.find(name);
    if (search != _database.end())
        is_function = search->second._invocation == FunctionInfo::FUNCTION;
   
    return is_function;
}

bool Function::isLeftAssociative(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._associativity != FunctionInfo::RIGHT;
    }
    else
        throw std::runtime_error("No such function");
}

bool Function::isRightAssociative(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._associativity != FunctionInfo::LEFT;
    }
    else
        throw std::runtime_error("No such function");
}

bool Function::isLeftAssociative() const {
    return _database[_name]._associativity != FunctionInfo::RIGHT;
}

bool Function::isRightAssociative() const {
    return _database[_name]._associativity != FunctionInfo::LEFT;
}

unsigned Function::getArity(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._arity;
    }
    else
        throw std::runtime_error("No such function");
}

unsigned Function::getPriority(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._priority;
    }
    else
        throw std::runtime_error("No such function");
}

FunctionInfo::InvocationType Function::getInvocationType(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._invocation;
    }
    else
        throw std::runtime_error("No such function");
}

FunctionInfo::AssociativityType Function::getAssociativityType(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._associativity;
    }
    else
        throw std::runtime_error("No such function");
}

bool Function::isOperator() const {
    return _database[_name]._invocation == FunctionInfo::OPERATOR;
}

bool Function::isFunction() const
{
    return _database[_name]._invocation == FunctionInfo::FUNCTION;
}



