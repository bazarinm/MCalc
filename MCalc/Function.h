#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include <vector>
#include <map>
#include <string>
#include <functional>

class Function
{
public:
    enum class AssociativityTypes { LEFT, RIGHT, BOTH };

    enum class Priorities : unsigned {
        ASSIGNMENT = 0,
        SUMMATION = 1, MULTIPLICATION = 2,
        POWER = 3, FUNCTION = 4,
    };

private:
    using Arguments = const std::vector<Variable>&;
    using ArgumentTypesVector = std::vector<Variable::Types>;
    using FunctionBody = std::function<Variable(std::vector<Variable>)>;

    struct FunctionInfo {
        unsigned _arity;
        Priorities _priority;
        AssociativityTypes _associativity;

        std::map<ArgumentTypesVector, FunctionBody> _function;
    };

public:
    Function();
    Function(const std::string&);

    Variable operator()(const std::vector<Variable>&) const;

    std::string getName() const;
    unsigned getArity() const;
    unsigned getPriority() const;
    AssociativityTypes getAssociativityType() const;
    bool isLeftAssociative() const;
    bool isRightAssociative() const;

    static bool isFunction(const std::string&);

    static unsigned getArity(const std::string&);
    static unsigned getPriority(const std::string&);
    static AssociativityTypes getAssociativityType(const std::string&);
    static bool isLeftAssociative(const std::string&);
    static bool isRightAssociative(const std::string&);

private:
    std::string _name;
    FunctionInfo _this_function_info;

    static std::map<std::string, FunctionInfo> _database;
};

#endif

