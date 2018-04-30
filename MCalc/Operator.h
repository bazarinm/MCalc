#ifndef OPERATOR_H
#define OPERATOR_H

#include "Token.h"

#include "Function.h"
#include "Variable.h"
#include <vector>

class Operator :
    public Token
{
public:
    Operator(std::string name);
    virtual ~Operator() = default;
    
    Function invoke;
};

#endif

