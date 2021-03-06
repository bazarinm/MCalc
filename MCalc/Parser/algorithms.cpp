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
        Lexer parser(Lexer::OnUnprocessable::STOP);
        for (const auto& character : input) {
            try {
                parser.process(character);
            }
            catch (const std::runtime_error& err) {
                throw ExecutionError(err.what());
            }
        }
        try {
            parser.endOfInput();
        }
        catch (const std::runtime_error& err) {
            throw ExecutionError(err.what());
        }

        return parser.getResult();
    }

    //TO DO: maybe remake this with switch
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

                //wtf I dont even get what is going on
                //TO DO: simplify this
                while (
                    !(stack.empty() || stack.top().isOpenBracket()) 
                    && ((stack.top().getPriority() > token_priority) 
                        || (stack.top().getPriority() == token_priority 
                            && token.isLeftAssociative()))) {
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

    Variable evaluate(const std::vector<Token>& sorted_tokens) {
        std::stack<Token> variable_tokens;
        std::vector<Variable> arguments;

        for (const auto& token : sorted_tokens) 
            switch (token.getType()) 
            {
            case Token::Types::OPERAND: 
                variable_tokens.push(token); 
                break;

            case Token::Types::OPERATOR: 
                for (unsigned i = 0; i < token.getArity(); ++i) {
                    if (variable_tokens.empty())
                        throw ExecutionError("input: too few variables ");

                    arguments.push_back(variable_tokens.top().getVariable());
                    variable_tokens.pop();
                }
                std::reverse(arguments.begin(), arguments.end());
                try {
                    variable_tokens.push(token.invoke(arguments));
                }
                catch (const std::runtime_error& err) {
                    throw ExecutionError(err.what());
                }
                arguments.clear();
                break;

            case Token::Types::BRACKET:
                throw ExecutionError("evaluation: extra open bracket(s) ");

            default: 
                throw std::runtime_error("evaluation: unknown token type ");
            }

        switch (variable_tokens.size())
        {
        case 0:
            return Variable();

        case 1:
            return variable_tokens.top().getVariable();

        default:
            throw ExecutionError("input: there are unused variables ");
        }
    }


} //namespace ShuntingYard end
