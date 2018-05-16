#ifndef LEXER_H
#define LEXER_H

#include "Matrix.h"
#include "Token.h"
#include <vector>
#include <exception>
#include <string>

class parsingError : public std::runtime_error {
public:
    parsingError(const std::string& msg) : std::runtime_error(msg) {}
};

class Lexer
{
private:
    enum States {
        PENDING,
        MINUS,
        INTEGER_PART,
        FRACTIONAL_PART,
        SYMBOL,
        WORD,
        BRACKET,
        MATRIX,
        UNPROCESSABLE,
    };

    const bool ignore_unprocessable = false;

public:
    Lexer();

    void process(char);
    void endOfInput();

    std::vector<Token> getResult() const;

private:
    States _state;
    std::string _buffer;
    std::vector<Token> _result;

    bool isNumber(const std::string&) const;
    bool isRoundBracket(char);
    bool isWordStart(char);
    bool isSquareBracket(char);
    bool isUnprocessable(char);
    bool isMinus(char);
    bool isInWord(char);
    bool isSpecialSymbol(char);

    Matrix stringToMatrix(const std::string&);

    void pending(char);
    void minus(char);
    void integer_part(char);
    void fractional_part(char);
    void symbol(char);
    void word(char);
    void bracket(char);
    void matrix(char);
    void unprocessable(char);
};

#endif
