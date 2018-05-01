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
    enum AccotiativityType { LEFT, RIGHT, BOTH };

    FunctionInfo(
        unsigned arity, unsigned priority,
        InvocationType invocation, AccotiativityType associativity,
        std::vector<std::pair<ArgumentTypesVector, FunctionBody>> function
    ) : _arity(arity), _priority(priority),
        _invocation(invocation), _associativity(associativity),
        _function(function) {};

    unsigned _arity;
    unsigned _priority;
    InvocationType _invocation;
    AccotiativityType _associativity;

    std::vector<std::pair<ArgumentTypesVector, FunctionBody>> _function;
};

static std::map<std::string, FunctionInfo> database = {
    {
        "det", //name
        FunctionInfo(
            1, 2,
            FunctionInfo::OPERATOR, FunctionInfo::BOTH,
            {
                {
                    { Variable::MATRIX },
                    [](std::vector<Variable> args) -> Variable { return args[0].matrix().determinant(); }
                }
            }
        )
    },
    {
        "*", //name
        FunctionInfo(
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
        )
    },
    {
        "+", //name
        FunctionInfo(
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
        )
    }
};

#endif
