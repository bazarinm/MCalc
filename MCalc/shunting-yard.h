#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <vector>
#include <string>
#include <stack>
#include "Token.h"

bool normal(Token a, Token b) {
	return (a.getPriority() < b.getPriority()); // || (a.getPriority() == b.getPriority() && b.isRi
}

bool notNormal(Token a, Token b) {
	return (a.getPriority() > b.getPriority()); // || (a.getPriority() == b.getPriority() && b.isRi
}

std::vector<Token> shunting_yard(const std::vector<Token>& tokens) {
	std::vector<Token> output;
	std::stack<Token> stack;

	for (auto token : tokens) {
		if (token.isOperand()) {
			output.push_back(token);
		}
		else if (token.isBracket()) {
			continue;
		}
		else if (stack.empty() || stack.top().isBracket()) {
			stack.push(token);
		}
		else if (normal(stack.top(), token)) {
			stack.push(token);
		}
		else if (notNormal(stack.top(), token)) {
			output.push_back(stack.top());
			stack.pop();

			while (!stack.empty() && notNormal(stack.top(), token)) {
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