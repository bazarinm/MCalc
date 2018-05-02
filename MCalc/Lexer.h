#ifndef LEXER_H
#define LEXER_H

#include "Matrix.h"
#include "Token.h"
#include <vector>
#include <string>

class Lexer
{
public:
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

    Lexer();

    void process(const std::string&);
    void endOfStr();

    std::vector<Token> getResult() const;
private:
    States _state;
    std::string _buffer;
    std::vector<Token> _result;

    bool isDigit(const std::string&);
    bool isAlpha(const std::string&);
    bool isBracket(const std::string&);
    bool isSquareBracket(const std::string&);
    bool isSpace(const std::string&);
    bool isUnprocessable(const std::string&);
    bool isWordCharacter(const std::string&);
    Matrix strToMatrix(const std::string& character);

    void pending(const std::string&);
    void minus(const std::string&);
    void integer_part(const std::string&);
    void fractional_part(const std::string&);
    void symbol(const std::string&);
    void word(const std::string&);
    void bracket(const std::string&);
    void matrix(const std::string&);
    void unprocessable(const std::string&);
};

#endif
