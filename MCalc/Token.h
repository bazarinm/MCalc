#ifndef TOKEN_H
#define TOKEN_H

#include "Variable.h"
#include "Function.h"
#include <string>

class Token
{
public:
    enum Types {OPERATOR, OPERAND, BRACKET};

    Token(Types, const std::string&);
    Token(const Variable&);
    Token(const Function&);

    Types getType() const;
    std::string getName() const;

    Variable getVariable() const;
    Variable invoke(const std::vector<Variable>&) const;

    bool isOperand() const;
    bool isOperator() const;
    bool isBracket() const;
    bool isOpenBracket() const;
    bool isCloseBracket() const;

    unsigned getArity() const;
    unsigned getPriority() const;
private:
    Types _type;
    std::string _name;

    Variable _variable;
    Function _function;
};

#endif

