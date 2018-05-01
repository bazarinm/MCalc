#include "FSM.h"

#include "Function.h"
#include "Variable.h"
#include <vector>
#include <string>
#include <cctype>

FSM::FSM() : _state(PENDING) {}


void FSM::process(const std::string& ch) {
    switch (_state) {
    case PENDING: pending(ch); break;
    case MINUS: minus(ch); break;
    case INTEGER_PART: integer_part(ch); break;
    case FRACTIONAL_PART: fractional_part(ch); break;
    case _OPERATOR: _operator(ch); break;
    case WORD: word(ch); break;
    case BRACKET: bracket(ch); break;
    case MATRIX: matrix(ch); break;
    }
}

std::vector<Token> FSM::getResult() const {
    return _result;
};

void FSM::endOfStr() {
    process("\n");
}



void FSM::pending(const std::string& str) {
    if (str == "-") {
        _buffer += str;
        _state = MINUS;
    }
    else if (Function::isOperator(str)) {
        _buffer += str;
        _state = _OPERATOR;
    }
    else if (isDigit(str)) {
        _buffer += str;
        _state = INTEGER_PART;
    }
    else if (isAlpha(str) || str == "_") {
        _buffer += str;
        _state = WORD;
    }
    else if (isBracket(str)) {
        _buffer += str;
        _state = BRACKET;
    }
    else if (str == "[") {
        _buffer += str;
        _state = MATRIX;
    }
}

void FSM::minus(const std::string& str) {
    if (isDigit(str)) {
        _buffer += str;
        _state = INTEGER_PART;
    }
    else {
        if (Function::isOperator("-"))
            _result.emplace_back(Token::OPERATOR, _buffer);
        _buffer = "";
        _state = PENDING;
        process(str);
    }
}

void FSM::integer_part(const std::string& str) {
    if (str == ".") {
        _buffer += str;
        _state = FRACTIONAL_PART;
    }
    else if (isDigit(str))
        _buffer += str;
    else {
        _result.emplace_back(std::stod(_buffer));
        _buffer = "";
        _state = PENDING;
        process(str);
    }
}

void FSM::fractional_part(const std::string& str) {
    if (isDigit(str))
        _buffer += str;
    else {
        _result.emplace_back(std::stod(_buffer));
        _buffer = "";
        _state = PENDING;
        process(str);
    }
}

void FSM::_operator(const std::string& str) {
    _result.emplace_back(Token::OPERATOR, _buffer);
    _buffer = "";
    _state = PENDING;
    process(str);
}

void FSM::word(const std::string& str) {
    if (isAlpha(str) || isDigit(str) || str == "_")
        _buffer += str;
    else {
        if (Variable::isVariable(_buffer))
            _result.emplace_back(Token::OPERAND, _buffer);
        else if (Function::isFunction(_buffer))
            _result.emplace_back(Token::OPERATOR, _buffer);
        _buffer = "";
        _state = PENDING;
        process(str);
    }
}

void FSM::bracket(const std::string& str) {
    _result.emplace_back(Token::BRACKET, _buffer);    
    _buffer = "";
    _state = PENDING;
    process(str);
}

void FSM::matrix(const std::string& str) {
    if (str == "]") {
        _buffer += str;
        //_result.push_back(_buffer);      STR TO MATRIX
        _buffer = "";
        _state = PENDING;
    }
    else
        _buffer += str;
}



bool FSM::isDigit(const std::string& str) {
    bool isDigit = true;

    if (str.length() != 1 || !isdigit(str[0]))
        isDigit = false;

    return isDigit;
}
bool FSM::isAlpha(const std::string& str) {
    bool isAlpha = true;

    if (str.length() != 1 || !isalpha(str[0]))
        isAlpha = false;

    return isAlpha;
}
bool FSM::isBracket(const std::string& str) {
    return str == "(" || str == ")";
}

