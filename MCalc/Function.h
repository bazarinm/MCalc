#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include <vector>
#include <map>
#include <string>
#include <functional>

using ArgumentTypesVector = std::vector<Variable::Types>;
using FunctionBody = std::function<Variable(std::vector<Variable>)>;

struct FunctionInfo {
    enum AssociativityTypes { LEFT, RIGHT, BOTH };

    unsigned _arity;
    unsigned _priority;
    AssociativityTypes _associativity;

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
    FunctionInfo::AssociativityTypes getAssociativityType() const;
    bool isLeftAssociative() const;
    bool isRightAssociative() const;

    static unsigned getArity(const std::string&);
    static unsigned getPriority(const std::string&);
    static FunctionInfo::AssociativityTypes getAssociativityType(const std::string&);
    static bool isFunction(const std::string&);
    static bool isLeftAssociative(const std::string&);
    static bool isRightAssociative(const std::string&);
private:
    std::string _name;
    FunctionInfo _this_function_info;

    static std::map<std::string, FunctionInfo> _database;
};

#endif

