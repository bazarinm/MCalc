#ifndef MCALC_H
#define MCALC_H

#include "Variable.h"
#include "Token.h"
#include <string>
#include <map>

class MCalc
{
public:
    MCalc();

    void start();
private:
    std::map<std::string, Variable> _variables;

    std::vector<Token> tokenize(std::string&);
    std::vector<Token> sort(std::vector<Token>);
    Variable evaluate(std::vector<Token>);
};

#endif

