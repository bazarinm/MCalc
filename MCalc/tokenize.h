#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <iostream>
#include <vector>
#include <string>
#include "Lexer.h"
#include "Token.h"


std::vector<Token> tokenize(const std::string& str) {
    Lexer parser;

    for (char ch : str) {
        parser.process(std::string(1, ch));
    }
    parser.endOfStr();

    return parser.getResult();
}

#endif