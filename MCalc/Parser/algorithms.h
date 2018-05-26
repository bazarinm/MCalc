#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "./Entities/Variable.h"
#include "Utils/Token.h"
#include <stdexcept>
#include <vector>
#include <string>

class ExecutionError : public std::runtime_error {
public:
    ExecutionError(const std::string&);
};

namespace ShuntingYard {
    std::vector<Token> tokenize(const std::string& input);
    std::vector<Token> sort(const std::vector<Token>& tokens);
    Variable evaluate(const std::vector<Token>& sorted_tokens);
}

#endif