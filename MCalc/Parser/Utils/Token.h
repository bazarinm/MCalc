#ifndef TOKEN_H
#define TOKEN_H

#include "./Entities/Function.h"
#include "./Entities/Variable.h"
#include <vector>
#include <string>

class Token
{
public:
    enum Types { OPERATOR, OPERAND, BRACKET };

    Token(Types type, const std::string&);
    Token(const Variable&);
    Token(const Function&);

    Types getType() const;

    std::string getName() const;
    Variable getVariable() const;
    Function getFunction() const;

    bool isOperand() const;
    bool isOperator() const;
    bool isBracket() const;

    Variable invoke(const std::vector<Variable>&) const;

    bool isOpenBracket() const;
    bool isCloseBracket() const;

    unsigned getArity() const;
    unsigned getPriority() const;
    bool isLeftAssociative() const;
    bool isRightAssociative() const;
private:
    Types _type;
    std::string _name;

    Variable _variable;
    Function _function;
};

#endif
