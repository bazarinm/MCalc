#ifndef OPERAND_H
#define OPERAND_H

#include "Token.h"

#include "Variable.h"
#include <string>

class Operand :
    public Token
{
public:
    Operand(const Variable&);
    Operand(const std::string& name);
    virtual ~Operand() = default;

    Variable getVariable() const;
private:
    Variable _variable;
};

#endif

