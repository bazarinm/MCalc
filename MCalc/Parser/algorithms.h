#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../Entities/Variable.h"
#include "./Utils/Token.h"
#include <exception>
#include <vector>
#include <string>

class ExecutionError : public std::runtime_error {
public:
    ExecutionError(const std::string& msg);
};

namespace ShuntingYard {
    std::vector<Token> tokenize(const std::string & input);
    std::vector<Token> sort(const std::vector<Token>& tokens);
    Variable evaluate(const std::vector<Token>& sorted_input);
}

#endif