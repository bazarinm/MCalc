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
    Function(const std::string&);
    
    Variable operator()(std::vector<Variable>);

    std::string getName() const;
    unsigned getArity() const;
    unsigned getPriority() const;
    bool isOperator() const;
    static bool isOperator(const std::string& name);
    bool isLeftAssociative() const;
    bool isRightAssociative() const;
private:
    std::string _name;
    unsigned _arity;
    unsigned _priority;
    FunctionInfo::InvocationType _invocation;
    FunctionInfo::AccotiativityType _associativity;

    std::map<ArgumentTypesVector, FunctionBody> _function;
};

#endif

