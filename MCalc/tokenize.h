#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "Lexer.h"
#include "Token.h"
#include <vector>
#include <string>

std::vector<Token> tokenize(const std::string& input) {
    Lexer parser;

    for (char character : input) {
        parser.process(character);
    }
    parser.endOfInput();

    return parser.getResult();
}

#endif