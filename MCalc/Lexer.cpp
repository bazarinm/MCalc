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
bool Lexer::isWordCharacter(const std::string& character) {
    return isAlpha(character) || isDigit(character) || character == "_";
}

bool Lexer::isBracket(const std::string& str) {
    return str == "(" || str == ")";
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
        else { //variable
            _result.emplace_back(Token::OPERAND, _buffer);
        }
        _buffer = "";
        _state = PENDING;
        process(character);
    }
}

void Lexer::bracket(const std::string& str) {
    _result.emplace_back(Token::BRACKET, _buffer);
    _buffer = "";
    _state = PENDING;
    process(str);
}

void Lexer::matrix(const std::string& str) {
    if (str == "]") {
        _buffer.append(str);
        // TODO: str to matrix
        //_result.push_back(_buffer);
        _buffer = "";
        _state = PENDING;
    }
    else {
        _buffer.append(str);
    }
}

