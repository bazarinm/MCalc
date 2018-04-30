#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include <functional>
#include <vector>
#include <map>
#include <string>

class Function
{
public:
    enum InvocationType {FUNCTION, OPERATOR};
    enum AccotiativityType {LEFT, RIGHT, BOTH};

    Function(const std::string&);
    
    Variable operator()(std::vector<Variable>);

    std::string getName() const;
    unsigned getArity() const;
    unsigned getPriority() const;
    bool isOperator() const;
    bool isLeftAssociative() const;
    bool isRightAssociative() const;
private:
    std::string _name;
    unsigned _arity;
    unsigned _priority;
    InvocationType _invocation;
    AccotiativityType _associativity;

    std::map<
        std::vector<Variable::Type>, //left to right
        bool
    > _arguments;

    std::map<
        std::vector<Variable::Type>, //left to right
        std::function<Variable(std::vector<Variable>)>
    > _function;
};

#endif

