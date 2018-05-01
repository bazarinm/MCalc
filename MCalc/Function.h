#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include "Database.h"
#include <vector>
#include <map>
#include <string>

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
    //std::map<ArgumentTypesVector, FunctionBody> _function;

    static std::map<std::string, FunctionInfo> _database;
};

#endif

