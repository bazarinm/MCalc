#ifndef EVALUATE_H
#define EVALUATE_H

#include "Token.h"
#include <algorithm>
#include <vector>
#include <stack>

Variable evaluate(const std::vector<Token>& sorted_input) {
    std::stack<Token> variables;
    std::vector<Variable> arguments;

    for (const Token& token : sorted_input) {
        if (token.isOperand()) {
            variables.push(token);
        }
        else if (token.isOperator()) {
            for (unsigned i = 0; i < token.getArity(); ++i) {
                if (variables.empty())
                    throw std::runtime_error("too many arguments");

                arguments.push_back(variables.top().getVariable());
                variables.pop();
            }

            std::reverse(arguments.begin(), arguments.end());
            variables.push(token.invoke(arguments));
            arguments.clear();
        }
        else
            throw std::runtime_error("why brackets?");
    }

    if (variables.size() == 1)
        return variables.top().getVariable();
    else
        throw std::runtime_error("wtf");
}


#endif
