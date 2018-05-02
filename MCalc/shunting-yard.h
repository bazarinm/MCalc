#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <vector>
#include <string>
#include <stack>
#include "Token.h"

bool priorityIsGreaterOrEqualAndTokenIsLeftAssociative(const Token& stackTop, const Token& token) {
    return (stackTop.getPriority() > token.getPriority()) || (stackTop.getPriority() == token.getPriority() && token.isLeftAssociative());
}

std::vector<Token> shunting_yard(const std::vector<Token>& tokens) {
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
            while (!stack.top().isOpenBracket()) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }
        else if (stack.empty() || stack.top().isOpenBracket()) {
            stack.push(token);
        }
        else {
            unsigned tokenPriority = token.getPriority();
            unsigned stackTopPriority = stack.top().getPriority();

            while (!(stack.empty() || stack.top().isOpenBracket())
                    && priorityIsGreaterOrEqualAndTokenIsLeftAssociative(stack.top(), token)) {
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