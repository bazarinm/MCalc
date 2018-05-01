#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include "Database.h"
#include <vector>
#include <map>
#include <string>

class Function
{
public:
    Function() = default;
    Function(const std::string&);
    
    Variable operator()(const std::vector<Variable>&);

    std::string getName() const;

    unsigned getArity() const;
    unsigned getPriority() const;
    bool isOperator() const;
    bool isLeftAssociative() const;
    bool isRightAssociative() const;

    static bool isOperator(const std::string&);
    static bool isFunction(const std::string&);
    static unsigned getArity(const std::string&);
    static unsigned getPriority(const std::string&);
    static bool isLeftAssociative(const std::string&);
    static bool isRightAssociative(const std::string&);
private:
    std::string _name;
    unsigned _arity;
    unsigned _priority;
    FunctionInfo::InvocationType _invocation;
    FunctionInfo::AssociativityType _associativity;

    std::map<ArgumentTypesVector, FunctionBody> _function;
};

#endif

