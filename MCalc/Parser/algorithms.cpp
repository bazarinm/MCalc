#include "algorithms.h"

#include "./Entities/Variable.h"
#include "Utils/Token.h"
#include "Utils/Lexer.h"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include <stack>

ExecutionError::ExecutionError(const std::string& msg) : std::runtime_error(msg) 
{
}

namespace ShuntingYard {

    std::vector<Token> tokenize(const std::string& input) {
        Lexer parser;
        for (char character : input) {
            try {
                parser.process(character);
            }
            catch (const std::runtime_error& err) {
                throw ExecutionError(err.what());
            }
        }
        parser.endOfInput();

        return parser.getResult();
    }

    std::vector<Token> sort(const std::vector<Token>& tokens) {
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
                    throw ExecutionError("sorting: extra close bracket(s) ");
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

    Variable evaluate(const std::vector<Token>& sorted_input) {
        std::stack<Token> variable_tokens;
        std::vector<Variable> arguments;

        for (const Token& token : sorted_input) {
            if (token.isOperand())
                variable_tokens.push(token);
            else if (token.isOperator()) {
                for (unsigned i = 0; i < token.getArity(); ++i) {
                    if (variable_tokens.empty())
                        throw ExecutionError("input: too few variables ");

                    arguments.push_back(variable_tokens.top().getVariable());
                    variable_tokens.pop();
                }

                std::reverse(arguments.begin(), arguments.end());

                try {
                    Variable result = token.invoke(arguments);
                    variable_tokens.push(result);
                }
                catch (const std::runtime_error& err) {
                    throw ExecutionError(err.what());
                }

                arguments.clear();
            }
            else
                throw ExecutionError("evaluation: extra open bracket(s) ");
        }

        Variable result;
        if (variable_tokens.size() == 1)
            result = variable_tokens.top().getVariable();
        else if (variable_tokens.size() != 0)
            throw ExecutionError("input: there are unused variables ");

        return result;
    }


} //namespace ShuntingYard end
