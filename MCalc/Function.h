#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include <vector>
#include <map>
#include <string>
#include <functional>

using ArgumentTypesVector = std::vector<Variable::Type>;
using FunctionBody = std::function<Variable(std::vector<Variable>)>;

struct FunctionInfo {
    enum InvocationType { FUNCTION, OPERATOR };
    enum AssociativityType { LEFT, RIGHT, BOTH };

    unsigned _arity;
    unsigned _priority;
    InvocationType _invocation;
    AssociativityType _associativity;

    std::map<ArgumentTypesVector, FunctionBody> _function;
};

class Function
{
public:
    Function();
    Function(const std::string&);
    
    Variable operator()(const std::vector<Variable>&) const;

    std::string getName() const;
    unsigned getArity() const;
    unsigned getPriority() const;
    FunctionInfo::InvocationType getInvocationType() const;
    FunctionInfo::AssociativityType getAssociativityType() const;
    bool isOperator() const;
    bool isFunction() const;
    bool isLeftAssociative() const;
    bool isRightAssociative() const;

    static unsigned getArity(const std::string&);
    static unsigned getPriority(const std::string&);
    static FunctionInfo::InvocationType getInvocationType(const std::string&);
    static FunctionInfo::AssociativityType getAssociativityType(const std::string&);
    static bool isOperator(const std::string&);
    static bool isFunction(const std::string&);
    static bool isLeftAssociative(const std::string&);
    static bool isRightAssociative(const std::string&);
private:
    std::string _name;
    //std::map<ArgumentTypesVector, FunctionBody> _function;

    static std::map<std::string, FunctionInfo> _database;
};

#endif

