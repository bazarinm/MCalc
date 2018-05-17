#include "Function.h"

#include "Variable.h"
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <functional>

std::map<std::string, Function::FunctionInfo> Function::_database = {
    {
        "", 
        {
            0, 
            Priorities::ASSIGNMENT,
            AssociativityTypes::BOTH,
            {
                {
                    { },
                    [](Arguments args) -> Variable { return Variable(); }
                }
            }
        }
    }, //EXAMPLE

    {
        "=",
        {   
            2, 
            Priorities::ASSIGNMENT,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::VOID, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::Types::VOID, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::Types::MATRIX, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::Types::SCALAR, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return Variable::assign(args[0].getName(), args[1]); }
                },
            }
        }
    }, //ASSIGNMENT

    //DATABASE GOES HERE:

    {
        "det", 
        {
            1, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix().determinant(); }
                }
            }
        }
    },

    {
        "*", 
        {
            2, 
            Priorities::MULTIPLICATION,
            AssociativityTypes::BOTH,
            {
                {
                    { Variable::Types::MATRIX, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix() * args[1].getMatrix(); }
                },
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() * args[1].getScalar(); }
                },
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix() * args[1].getScalar(); }
                },
                {
                    { Variable::Types::SCALAR, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[1].getMatrix() * args[0].getScalar(); }
                },
            }
        }
    },

    {
        "+", 
        {
            2, 
            Priorities::SUMMATION,
            AssociativityTypes::BOTH,
            {
                {
                    { Variable::Types::MATRIX, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix() + args[1].getMatrix(); }
                },
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() + args[1].getScalar(); }
                },
            }
        }
    },

    {
        "inv", 
        {
            1, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix().inverse(); }
                },
            }
        }
    },

    {
        "least", 
        {
            2, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().least_squares(
                        static_cast<int>(std::abs(args[1].getScalar()))
                    ); }
                },
            }
        }
    },

    {
        "-", 
        {
            2, 
            Priorities::SUMMATION,
            AssociativityTypes::BOTH,
            {
                {
                    { Variable::Types::MATRIX, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix() - args[1].getMatrix(); }
                },
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() - args[1].getScalar(); }
                },
            }
        }
    },

    {
        "/",
        {
            2, 
            Priorities::MULTIPLICATION,
            AssociativityTypes::LEFT,
            {
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getScalar() / args[1].getScalar(); }
                },
                {
                    { Variable::Types::MATRIX, Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix() / args[1].getMatrix(); }
                },
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix() / args[1].getScalar(); }
                },
            }
        }   
    },

    {
        "eye",
        {
            1, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return Matrix(
                        Matrix::PredefinedSquareTypes::IDENTITY, 
                        static_cast<std::size_t>(std::abs(args[0].getScalar()))
                    ); }
                },
            }
        }   
    },

    {
        "diag",
        {
            1, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::MATRIX },
                    [](Arguments args) -> Variable 
                    { return Matrix(
                        Matrix::SquareTypes::DIAGONAL, 
                        args[0].getMatrix().getEntries().size(), 
                        args[0].getMatrix().getEntries()
                    ); }
                },
            }
        }   
    },

    {
        "zeros",
        {
            2, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return Matrix(
                        Matrix::PredefinedRectangleTypes::ZERO, 
                        static_cast<std::size_t>(std::abs(args[0].getScalar())),
                        static_cast<std::size_t>(std::abs(args[1].getScalar()))
                    ); }
                },
            }
        }   
    },

    {
        "rand",
        {
            2, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return Matrix(
                        Matrix::PredefinedRectangleTypes::RANDOM,
                        static_cast<std::size_t>(std::abs(args[0].getScalar())), 
                        static_cast<std::size_t>(std::abs(args[1].getScalar()))
                    ); }
                },
            }
        }   
    },

    {
        "'",
        {
            1, 
            Priorities::FUNCTION,
            AssociativityTypes::BOTH,
            {
                {
                    { Variable::Types::MATRIX },
                    [](Arguments args) -> Variable { return args[0].getMatrix().transpose(); }
                },
            }
        }   
    },

    {
        ":",
        {
            2, 
            Priorities::FUNCTION,
            AssociativityTypes::LEFT,
            {
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().getRow(
                        static_cast<std::size_t>(std::abs(args[1].getScalar()))
                    ); }
                },
            }
        }   
    },

    {
        ";",
        {
            2, 
            Priorities::FUNCTION,
            AssociativityTypes::LEFT,
            {
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().getColumn(
                        static_cast<std::size_t>(std::abs(args[1].getScalar()))
                    ); }
                },
            }
        }   
    },

    {
        "at",
        {
            3, 
            Priorities::FUNCTION,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return args[0].getMatrix().at(
                        static_cast<std::size_t>(std::abs(args[1].getScalar())),
                        static_cast<std::size_t>(std::abs(args[2].getScalar()))
                    ); }
                },
            }
        }   
    },

    {
        "^",
        {
            2, 
            Priorities::POWER,
            AssociativityTypes::RIGHT,
            {
                {
                    { Variable::Types::SCALAR, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return std::pow(args[0].getScalar(), args[1].getScalar()); }
                },
                {
                    { Variable::Types::MATRIX, Variable::Types::SCALAR },
                    [](Arguments args) -> Variable { return 
                    args[0].getMatrix() ^ static_cast<int>(args[1].getScalar()); }
                },
            }
        }   
    },

    //AND SO ON
};

Function::Function() : Function("") 
{
}

Function::Function(const std::string& name) : _name(name) 
{
    auto search = _database.find(name);
    if (search == _database.end())
        throw std::runtime_error("function: no function <" + name + "> ");
    else
        _this_function_info = search->second;
}

Variable Function::operator()(const std::vector<Variable>& arguments) const 
{
    ArgumentTypesVector argument_types;
    for (const Variable& argument : arguments)
        argument_types.push_back(argument.getType());

    std::string error_message = "function < " + _name + " >: ";

    auto search = _this_function_info._function.find(argument_types);
    if (search != _this_function_info._function.end())
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
            case Variable::Types::MATRIX: description += "Matrix "; break;
            case Variable::Types::SCALAR: description += "Scalar "; break;
            case Variable::Types::VOID: undefined_arguments = true; break;
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
    return _this_function_info._arity;
}

unsigned Function::getPriority() const {
    return static_cast<unsigned>(_this_function_info._priority);
}

Function::AssociativityTypes Function::getAssociativityType() const {
    return _this_function_info._associativity;
}

bool Function::isFunction(const std::string& name) {
    bool is_function = false;

    auto search = _database.find(name);
    if (search != _database.end())
        is_function = true;
   
    return is_function;
}

bool Function::isLeftAssociative(const std::string& name)
{
    bool isLeftAssociative = false;
    auto search = _database.find(name);
    if (search != _database.end()) {
        isLeftAssociative = search->second._associativity != AssociativityTypes::RIGHT;
    }
    else
        throw std::runtime_error("no function <" + name + "> ");

    return isLeftAssociative;
}

bool Function::isRightAssociative(const std::string& name)
{
    bool isRightAssociative = false;
    auto search = _database.find(name);
    if (search != _database.end()) {
        isRightAssociative = search->second._associativity != AssociativityTypes::LEFT;
    }
    else
        throw std::runtime_error("no function <" + name + "> ");

    return isRightAssociative;
}

bool Function::isLeftAssociative() const {
    return _this_function_info._associativity != AssociativityTypes::RIGHT;
}

bool Function::isRightAssociative() const {
    return _this_function_info._associativity != AssociativityTypes::LEFT;
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
        return static_cast<unsigned>(search->second._priority);
    }
    else
        throw std::runtime_error("no function <" + name + "> ");
}

Function::AssociativityTypes Function::getAssociativityType(const std::string& name)
{
    auto search = _database.find(name);
    if (search != _database.end()) {
        return search->second._associativity;
    }
    else
        throw std::runtime_error("no function <" + name + "> ");
}



