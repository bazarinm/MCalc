#ifndef MCALC_H
#define MCALC_H

#include "Variable.h"
#include "Token.h"
#include "Function.h"
#include <string>
#include <map>

struct FunctionInfo;

class MCalc
{
public:
    MCalc();

    void start();
private:
    std::map<std::string, Variable> _variables;
    std::map<std::string, FunctionInfo> _functions;

    std::vector<Token> tokenize(std::string&);
    std::vector<Token> sort(std::vector<Token>);
    Variable evaluate(std::vector<Token>);

    bool isVariable(std::string&);
    bool isOperator(std::string&);
    bool isFunction(std::string&);
};

#endif

