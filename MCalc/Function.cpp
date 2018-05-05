#include "Function.h"

#include "Variable.h"
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <exception>
#include <functional>

const unsigned summation_priority = 1;
const unsigned multiplication_priority = 2;
const unsigned power_priority = 3;
const unsigned function_priority = 4;

using Arguments = const std::vector<Variable>&;

std::map<std::string, FunctionInfo> Function::_database = {
    {
        "", 
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
    }, //AUX

    {
        "=",
        {   
            2, 0,
            FunctionInfo::OPERATOR, FunctionInfo::RIGHT,
            {
                {
                    { Variable::VOID, Variable::SCALAR },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::VOID, Variable::MATRIX },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::SCALAR, Variable::MATRIX },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
            }
        }
    }, //ASSIGNMENT

    //DATABASE GOES HERE:
    {
        "det", 
        {
            1, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix().determinant(); }
                }
            }
        }
    },

    {
        "*", 
        {
            2, multiplication_priority,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix() * args[1].getMatrix(); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() * args[1].getScalar(); }
                },
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix() * args[1].getScalar(); }
                },
                {
                    { Variable::SCALAR, Variable::MATRIX },
                    [](Arguments args) -> Variable { return args[1].getMatrix() * args[0].getScalar(); }
                },
            }
        }
    },

    {
        "+", 
        {
            2, summation_priority,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix() + args[1].getMatrix(); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() + args[1].getScalar(); }
                },
            }
        }
    },

    {
        "inv", 
        {
            1, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix().inverse(); }
                },
            }
        }
    },

    {
        "least", 
        {
            2, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().least_squares((abs(args[1].getScalar()))); }
                },
            }
        }
    },

    {
        "-", 
        {
            2, summation_priority,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix() - args[1].getMatrix(); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() - args[1].getScalar(); }
                },
            }
        }
    },

    {
        "/",
        {
            2, multiplication_priority,
            FunctionInfo::OPERATOR, FunctionInfo::LEFT,
            {
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() / args[1].getScalar(); }
                },
            }
        }   
    },

    {
        "eye",
        {
            1, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::SCALAR },
                    [](Arguments args) -> Variable { return Matrix(Matrix::IDENTITY, abs(args[0].getScalar())); }
                },
            }
        }   
    },

    {
        "diag",
        {
            1, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::MATRIX },
                    [](Arguments args) -> Variable 
                    { return Matrix(Matrix::DIAGONAL, 
                        args[0].getMatrix().getEntries().size(), 
                        args[0].getMatrix().getEntries()); }
                },
            }
        }   
    },

    {
        "zeros",
        {
            2, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return Matrix(Matrix::ZERO, args[0].getScalar(), args[1].getScalar()); }
                },
            }
        }   
    },

    {
        "rand",
        {
            2, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return Matrix(Matrix::RANDOM, args[0].getScalar(), args[1].getScalar()); }
                },
            }
        }   
    },

    {
        "'",
        {
            1, function_priority,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix().transpose(); }
                },
            }
        }   
    },

    {
        ":",
        {
            2, function_priority,
            FunctionInfo::OPERATOR, FunctionInfo::LEFT,
            {
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().getRow(args[1].getScalar()); }
                },
            }
        }   
    },

    {
        ";",
        {
            2, function_priority,
            FunctionInfo::OPERATOR, FunctionInfo::LEFT,
            {
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().getColumn(args[1].getScalar()); }
                },
            }
        }   
    },

    {
        "at",
        {
            3, function_priority,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::MATRIX, Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().at(args[1].getScalar(), args[2].getScalar()); }
                },
            }
        }   
    },

    {
        "^",
        {
            2, power_priority,
            FunctionInfo::OPERATOR, FunctionInfo::RIGHT,
            {
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](Arguments args) -> Variable { return pow(args[0].getScalar(), args[1].getScalar()); }
                },
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix() ^ args[1].getScalar(); }
                },
            }
        }   
    },



    //AND SO ON
};

Function::Function() : _name("") {}

Function::Function(const std::string& name) : _name(name) {
    auto search = _database.find(name);
    if (search == _database.end()) 
        throw std::runtime_error("function: no function <" + name + "> ");
}

Variable Function::operator()(const std::vector<Variable>& arguments) const {
    ArgumentTypesVector argument_types;
    for (const Variable& argument : arguments)
        argument_types.push_back(argument.getType());

    std::string error_message = "function < " + _name + " >: ";

    auto search = _database[_name]._function.find(argument_types);
    if (search != _database[_name]._function.end())
        try {
            return search->second(arguments);
        }
        catch (const std::runtime_error err) {
            throw std::runtime_error(error_message + err.what());
        }
    else {
        std::string description = "";
        description += "does not take argument(s) < ";
        bool undefined_arguments = false;
        for (auto argument_type : argument_types) {
            switch (argument_type) {
            case Variable::MATRIX: description += "Matrix "; break;
            case Variable::SCALAR: description += "Scalar "; break;
            case Variable::VOID: undefined_arguments = true; break;
            }
        }
        if (undefined_arguments)
            description = "undefined argument(s) ";
        else
            description += "> ";

        throw std::runtime_error(error_message + description);
    }
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
    bool isLeftAssociative = false;
    auto search = _database.find(name);
    if (search != _database.end()) {
        isLeftAssociative = search->second._associativity != FunctionInfo::RIGHT;
    }
    return isLeftAssociative;
}

bool Function::isRightAssociative(const std::string& name)
{
    bool isRightAssociative = false;
    auto search = _database.find(name);
    if (search != _database.end()) {
        isRightAssociative = search->second._associativity != FunctionInfo::LEFT;
    }
    return isRightAssociative;
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
        throw std::runtime_error("no function <" + name + "> ");
}

unsigned Function::getPriority(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._priority;
    }
    else
        throw std::runtime_error("no function <" + name + "> ");
}

FunctionInfo::InvocationType Function::getInvocationType(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._invocation;
    }
    else
        throw std::runtime_error("no function <" + name + "> ");
}

FunctionInfo::AssociativityType Function::getAssociativityType(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._associativity;
    }
    else
        throw std::runtime_error("no function <" + name + "> ");
}

bool Function::isOperator() const {
    return _database[_name]._invocation == FunctionInfo::OPERATOR;
}

bool Function::isFunction() const
{
    return _database[_name]._invocation == FunctionInfo::FUNCTION;
}



