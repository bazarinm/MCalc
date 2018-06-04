#ifndef LEXER_H
#define LEXER_H

#include "./Entities/Matrix/Matrix.h"
#include "Token.h"
#include <vector>
#include <string>

class Lexer
{
public:
    enum class OnUnprocessable : bool {
        STOP, IGNORE
    };

private:
    enum class States {
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

public:
    Lexer();
    Lexer(OnUnprocessable);

    void process(char);
    void endOfInput();

    const std::vector<Token>& getResult() const;

private:
    States _state;
    std::string _buffer;
    std::vector<Token> _result;
    bool _ignore_unprocessable;

    bool isNumber(const std::string&) const;
    bool isRoundBracket(char) const;
    bool isWordStart(char) const;
    bool isSquareBracket(char) const;
    bool isMinus(char) const;
    bool isInWord(char) const;
    bool isSpecialSymbol(char) const;

    Matrix stringToMatrix(const std::string&) const;

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
