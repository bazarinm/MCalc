#ifndef EVALUATE_H
#define EVALUATE_H

#include "Token.h"
#include <algorithm>
#include <vector>
#include <stack>

const std::string answer_name = "ans";

Variable evaluate(const std::vector<Token>& sorted_input) {
    std::stack<Token> variable_tokens;
    std::vector<Variable> arguments;

    for (const Token& token : sorted_input) {
        if (token.isOperand()) {
            variable_tokens.push(token);
        }
        else if (token.isOperator()) {
            for (unsigned i = 0; i < token.getArity(); ++i) {
                if (variable_tokens.empty())
                    throw std::runtime_error("too many arguments");

                arguments.push_back(variable_tokens.top().getVariable());
                variable_tokens.pop();
            }

            std::reverse(arguments.begin(), arguments.end());
            variable_tokens.push(token.invoke(arguments));
            arguments.clear();
        }
        else
            throw std::runtime_error("why brackets?");
    }

    if (variable_tokens.size() == 1) {
        Variable result = variable_tokens.top().getVariable();
        if (result.isExpressionResult())
            return Variable::assign(answer_name, result);
        else
            return result;
    }
    else
        throw std::runtime_error("wtf");
}


#endif
