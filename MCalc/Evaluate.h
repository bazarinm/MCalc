#ifndef EVALUATE_H
#define EVALUATE_H

#include "Token.h"
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

const std::string answer_name = "ans";

class evaluationError : public std::runtime_error {
public:
    evaluationError(const std::string& msg) : std::runtime_error(msg) {}
};

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
                    throw evaluationError("input: too few arguments for function " + token.getName());

                arguments.push_back(variable_tokens.top().getVariable());
                variable_tokens.pop();
            }

            std::reverse(arguments.begin(), arguments.end());

            try {
                Variable result = token.invoke(arguments);
                variable_tokens.push(result);
            }
            catch (const std::runtime_error evaluation_error) {
                throw evaluationError(evaluation_error.what());
            }

            arguments.clear();
        }
        else
            throw std::runtime_error("program fault: brackets in sorted input");
    }

    if (variable_tokens.size() == 1) {
        Variable result = variable_tokens.top().getVariable();
        if (result.isExpressionResult())
            return Variable::assign(answer_name, result);
        else
            return result;
    }
    else
        throw evaluationError("input: there are extra variables");
}


#endif
