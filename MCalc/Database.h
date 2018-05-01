#ifndef DATABASE_H
#define DATABASE_H

#include "Variable.h"
#include <functional>
#include <vector>
#include <string>
#include <map>

using ArgumentTypesVector = std::vector<Variable::Type>;
using FunctionBody = std::function<Variable(std::vector<Variable>)>;

struct FunctionInfo {
    enum InvocationType { FUNCTION, OPERATOR };
    enum AssociativityType { LEFT, RIGHT, BOTH };

    unsigned _arity;
    unsigned _priority;
    InvocationType _invocation;
    AssociativityType _associativity;

    std::vector<std::pair<ArgumentTypesVector, FunctionBody>> _function;
};

static std::map<std::string, FunctionInfo> database = {
    {
        "det", //name
        {
            1, 2,
            FunctionInfo::FUNCTION, FunctionInfo::RIGHT,
            {
                {
                    { Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[0].matrix().determinant(); }
                }
            }
        }
    },

    {
        "*", //name
        {
            2, 2,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[0].matrix() * args[1].matrix(); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](std::vector<Variable> args) -> Variable { return args[0].scalar() * args[1].scalar(); }
                },
                {
                    { Variable::MATRIX, Variable::SCALAR },
                    [](std::vector<Variable> args) -> Variable { return args[0].matrix() * args[1].scalar(); }
                },
                {
                    { Variable::SCALAR, Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[1].matrix() * args[0].scalar(); }
                },
            }
        }
    },

    {
        "+", //name
        {
            2, 1,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX, Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[0].matrix() + args[1].matrix(); }
                },
                {
                    { Variable::SCALAR, Variable::SCALAR },
                    [](std::vector<Variable> args) -> Variable { return args[0].scalar() + args[1].scalar(); }
                },
            }
        }
    }
};

#endif
