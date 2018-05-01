#ifndef TEMP_FSM_H
#define TEMP_FSM_H

#include "Function.h"
#include "Variable.h"
#include "Token.h"
#include "Operand.h"
#include "Operator.h"
#include <vector>
#include <cctype>
#include <string>

enum States {
    PENDING, MINUS,
    INTEGER_PART,
    FRACTIONAL_PART,
    _OPERATOR, WORD,
    BRACKET, MATRIX,
};


class FSM 
{
public:
    
    FSM() : _state(PENDING) {}

    std::vector<Token> getResult() {
        return _result;
    };

    void process(const std::string& ch) {
        switch (_state) {
        case PENDING : pending(ch); break;
        case MINUS : minus(ch); break;
        case INTEGER_PART : integer_part(ch); break;
        case FRACTIONAL_PART : fractional_part(ch); break;
        case _OPERATOR: _operator(ch); break;
        case WORD: word(ch); break;
        case BRACKET: bracket(ch); break;
        case MATRIX: matrix(ch); break;
        }
    }

private:
    States _state;
    std::string _buffer;
    std::vector<Token> _result;

    void pending(const std::string& ch) {
        if (ch == "-") {
            _buffer += ch;
            _state = MINUS;
        } 
        else if (Function::isOperator(ch)) {
            _buffer += ch;
            _state = _OPERATOR;
        } 
        else if (isDigit(ch)) {
            _buffer += ch;
            _state = INTEGER_PART;
        } 
        else if (isAlpha(ch) || ch == "_") {
            _buffer += ch;
            _state = WORD;
        } 
        else if (isBracket(ch)) {
            _buffer += ch;
            _state = BRACKET;
        } 
        else if (ch == "[") {
            _buffer += ch;
            _state = MATRIX;
        }
    }

    void minus(const std::string& ch) {
        if (isDigit(ch)) {
            _buffer += ch;
            _state = INTEGER_PART;
        } 
        else {
            if (Function::isOperator("-"))
                _result.push_back(Operator(_buffer));
            _buffer = "";
            _state = PENDING;
            process(ch);
        }
    }

    void integer_part(const std::string& ch) {
        if (ch == ".") {
            _buffer += ch;
            _state = FRACTIONAL_PART;
        } 
        else if (isDigit(ch))
            _buffer += ch;
        else {
            _result.push_back(Operand(std::stod(_buffer)));
            _buffer = "";
            _state = PENDING;
            process(ch);
        }
    }

    void fractional_part(const std::string& ch) {
        if (isDigit(ch))
            _buffer += ch;
        else {
            _result.push_back(Operand(std::stod(_buffer)));
            _buffer = "";
            _state = PENDING;
            process(ch);
        }
    }

    void _operator(const std::string& ch) {
        _result.push_back(Operator(_buffer));
        _buffer = "";
        _state = PENDING;
        process(ch);
    }

    void word(const std::string& ch) {
        if (isAlpha(ch) || isDigit(ch) || ch == "_")
            _buffer += ch;
        else {
            if (Variable::isVariable(_buffer))
                _result.push_back(Operand(_buffer));
            else if (Function::isFunction(_buffer))
                _result.push_back(Operator(_buffer));
            _buffer = "";
            _state = PENDING;
            process(ch);
        }
    }

    void bracket(const std::string& ch) {
        //_result.push_back(_buffer);              BRACKETS
        _buffer = "";
        _state = PENDING;
        process(ch);
    }

    void matrix(const std::string& ch) {
        if (ch == "]") {
            _buffer += ch;
            //_result.push_back(_buffer);      STR TO MATRIX
            _buffer = "";
            _state = PENDING;
        } 
        else 
            _buffer += ch;
    }

    bool isDigit(const std::string& str) {
        bool isDigit = true;

        if (str.length() != 1 || !isdigit(str[0]))
            isDigit = false;

        return isDigit;
    }
    bool isAlpha(const std::string& str) {
        bool isAlpha = true;

        if (str.length() != 1 || !isalpha(str[0]))
            isAlpha = false;

        return isAlpha;
    }
    bool isBracket(const std::string& str) {
        return str == "(" || str == ")";
    }

    void endOfStr() {
         process("\n");
    }

};

#endif //TEMP_FSM_H
