#include <vector>
#include <string>
#include <cctype>
#include "Lexer.h"
#include "Function.h"
#include "Variable.h"

Lexer::Lexer() : _state(PENDING) {}

std::vector<Token> Lexer::getResult() const {
    return _result;
};

bool Lexer::isDigit(const std::string& character) {
    return isdigit(character[0]);
}

bool Lexer::isAlpha(const std::string& character) {
    return isalpha(character[0]);
}

bool Lexer::isSpace(const std::string& character) {
    return isspace(character[0]);
}

bool Lexer::isUnprocessable(const std::string& character) {
    return !(isWordCharacter(character)
            || isBracket(character)
            || Function::isOperator(character)
            || isSquareBracket(character)
            || character == "-");
}

bool Lexer::isWordCharacter(const std::string& character) {
    return isAlpha(character) || isDigit(character) || character == "_";
}

bool Lexer::isBracket(const std::string& character) {
    return character == "(" || character == ")";
}

bool Lexer::isSquareBracket(const std::string& character) {
    return character == "[" || character == "]";
}

void Lexer::endOfStr() {
    process("\n");
}


void Lexer::process(const std::string& character) {
    switch (_state) {
    case PENDING: pending(character); break;
    case MINUS: minus(character); break;
    case INTEGER_PART: integer_part(character); break;
    case FRACTIONAL_PART: fractional_part(character); break;
    case SYMBOL: symbol(character); break;
    case WORD: word(character); break;
    case BRACKET: bracket(character); break;
    case MATRIX: matrix(character); break;
    case UNPROCESSABLE: unprocessable(character); break;
    }
}

void Lexer::pending(const std::string& character) {
    if (character == "-") {
        _buffer.append(character);
        _state = MINUS;
    }
    else if (Function::isOperator(character)) {
        _buffer.append(character);
        _state = SYMBOL;
    }
    else if (isDigit(character)) {
        _buffer.append(character);
        _state = INTEGER_PART;
    }
    else if (isAlpha(character) || character == "_") {
        _buffer.append(character);
        _state = WORD;
    }
    else if (isBracket(character)) {
        _buffer.append(character);
        _state = BRACKET;
    }
    else if (character == "[") {
        _buffer.append(character);
        _state = MATRIX;
    } else if (!isSpace(character)) {
        _buffer.append(character);
        _state = UNPROCESSABLE;
    }
}

void Lexer::minus(const std::string& character) {
    if (isDigit(character)) {
        _buffer.append(character);
        _state = INTEGER_PART;
    }
    else {
        _state = SYMBOL;
        symbol(character);
    }
}

void Lexer::integer_part(const std::string& character) {
    if (character == ".") {
        _buffer.append(character);
        _state = FRACTIONAL_PART;
    }
    else if (isDigit(character)) {
        _buffer.append(character);
    }
    else {
        _result.emplace_back(std::stod(_buffer));
        _buffer = "";
        _state = PENDING;
        process(character);
    }
}

void Lexer::fractional_part(const std::string& character) {
    if (isDigit(character)) {
        _buffer.append(character);
    }
    else {
        _result.emplace_back(std::stod(_buffer));
        _buffer = "";
        _state = PENDING;
        process(character);
    }
}
-
void Lexer::symbol(const std::string& character) {
    _result.emplace_back(Token::OPERATOR, _buffer);
    _buffer = "";
    _state = PENDING;
    process(character);
}

void Lexer::word(const std::string& character) {
    if (isWordCharacter(character)) {
        _buffer.append(character);
    }
    else {
        if (Function::isFunction(_buffer)) {
            _result.emplace_back(Token::OPERATOR, _buffer);
        }
        else {
            // TODO: consider if yet undefined operand
            _result.emplace_back(Token::OPERAND, _buffer);
        }
        _buffer = "";
        _state = PENDING;
        process(character);
    }
}

void Lexer::bracket(const std::string& character) {
    _result.emplace_back(Token::BRACKET, _buffer);
    _buffer = "";
    _state = PENDING;
    process(character);
}

void Lexer::matrix(const std::string& character) {
    if (character == "]") {
        _buffer.append(character);
        // TODO: str to matrix
        //_result.push_back(_buffer);
        _buffer = "";
        _state = PENDING;
    }
    else {
        _buffer.append(character);
    }
}

void Lexer::unprocessable(const std::string& character) {
    if (isUnprocessable(character)) {
        _buffer.append(character);
    } else {
        _buffer = "";
        _state = PENDING;
    }
}