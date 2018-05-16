#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include "Token.h"
#include <vector>
#include <string>
#include <stack>

class sortingError : public std::runtime_error {
public:
    sortingError(const std::string& msg) : std::runtime_error(msg) {}
};

std::vector<Token> shuntingYard(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::stack<Token> stack;

    for (const auto& token : tokens) {
        if (token.isOperand()) {
            output.push_back(token);
        }
        else if (token.isOpenBracket()) {
            stack.push(token);
        }
        else if (token.isCloseBracket()) {
            while (!stack.empty() && !stack.top().isOpenBracket()) {
                output.push_back(stack.top());
                stack.pop();
            }

            if (stack.empty())
                throw sortingError("sorting: extra close bracket(s) ");
            stack.pop();
        }
        else if (stack.empty() || stack.top().isOpenBracket()) {
            stack.push(token);
        }
        else {
            unsigned token_priority = token.getPriority();

            //I dont like the looks of this logical expression
            while (
                    !(stack.empty() || stack.top().isOpenBracket()) 
                    && (
                        (stack.top().getPriority() > token_priority) 
                        || (stack.top().getPriority() == token_priority && token.isLeftAssociative())
                    )
            ) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        }
    }

    while (!stack.empty()) {
        output.push_back(stack.top());
        stack.pop();
    }

    return output;
}

#endif