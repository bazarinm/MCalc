#ifndef OPERAND_H
#define OPERAND_H

#include "Token.h"

#include "Variable.h"

class Operand :
    public Token
{
public:
    Operand(Variable);
    virtual ~Operand() = default;

    Variable getVariable() const;
private:
    Variable _variable;
};

#endif

