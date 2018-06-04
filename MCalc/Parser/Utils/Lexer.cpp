#include "Lexer.h"

#include "./Entities/Function.h"
#include "./Entities/Matrix/Matrix.h"
#include "Token.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <regex>
#include <cctype>

Lexer::Lexer() : _state(States::PENDING), _ignore_unprocessable(false)
{
}

Lexer::Lexer(OnUnprocessable action) : 
    _state(States::PENDING), 
    _ignore_unprocessable(static_cast<bool>(action))
{
}

const std::vector<Token>& Lexer::getResult() const {
    return _result;
};

bool Lexer::isNumber(const std::string& str) const {
    return std::regex_match(str, std::regex("[-]?[0-9]+[.]?[0-9]*"));
}

bool Lexer::isMinus(char character) const {
    return character == '-';
}

bool Lexer::isWordStart(char character) const {
    return std::isalpha(character) || character == '_';
}


bool Lexer::isInWord(char character) const {
    return isWordStart(character) || std::isdigit(character);
}

/* any special symbols that do not fit into other categories */
bool Lexer::isSpecialSymbol(char character) const {
    return !(0
        || std::isspace(character)
        || std::isdigit(character)
        || isWordStart(character)
        || isInWord(character)
        || isRoundBracket(character)
        || isSquareBracket(character)
        );
}

bool Lexer::isRoundBracket(char character) const {
    return character == '(' || character == ')';
}


bool Lexer::isSquareBracket(char character) const {
    return character == '[' || character == ']';
}

void Lexer::endOfInput() {
    process('\n');
}

//TO DO: remake this
Matrix Lexer::stringToMatrix(const std::string& matrixString) const 
{
    std::vector<std::string> splitedMatrixStr;
    std::string buffer;
    for (char character : matrixString) {
        if (character == ';') {
            splitedMatrixStr.push_back(buffer);
            buffer = "";
        }
        else {
            buffer.push_back(character);
        }
    }

    splitedMatrixStr.push_back(buffer);
    buffer = "";

    bool pending = true;
    std::vector<std::vector<double>> matrixVector;
    for (auto strRow : splitedMatrixStr) {
        std::vector<double> bufferRow;
        for (auto character : strRow) {
            if (isspace(character) && !pending) {
                if (isNumber(buffer))
                    bufferRow.push_back(std::stod(buffer));
                else
                    throw std::runtime_error("parser: incorrect symbol < " + buffer + " > in matrix initialization");

                buffer = "";
                pending = true;
            }
            else if (!isspace(character)) {
                buffer.push_back(character);
                pending = false;
            }
        }
        if (!buffer.empty()) {
            if (isNumber(buffer))
                bufferRow.push_back(std::stod(buffer));
            else
                throw std::runtime_error("parser: incorrect symbol < " + buffer + " > in matrix initialization");

            buffer = "";
            pending = true;
        }
        if (!bufferRow.empty()) {
            matrixVector.push_back(bufferRow);
        }
    }

    return Matrix(matrixVector); 
};

void Lexer::process(char character) 
{
    switch (_state) 
    {
    case States::PENDING: pending(character); break;
    case States::MINUS: minus(character); break;
    case States::INTEGER_PART: integer_part(character); break;
    case States::FRACTIONAL_PART: fractional_part(character); break;
    case States::SYMBOL: symbol(character); break;
    case States::WORD: word(character); break;
    case States::BRACKET: bracket(character); break;
    case States::MATRIX: matrix(character); break;
    case States::UNPROCESSABLE: unprocessable(character); break;
    }
}

void Lexer::pending(char character) 
{
    if (isMinus(character)) {
        _buffer.push_back(character);
        _state = States::MINUS;
    }
    else if (std::isdigit(character)) {
        _buffer.push_back(character);
        _state = States::INTEGER_PART;
    }
    else if (isWordStart(character)) {
        _buffer.push_back(character);
        _state = States::WORD;
    }
    else if (isRoundBracket(character)) {
        _buffer.push_back(character);
        _state = States::BRACKET;
    }
    else if (character == '[') {
        // _buffer.push_back(character);
        _state = States::MATRIX;
    }
    else if (isSpecialSymbol(character)) {
        _buffer.push_back(character);
        _state = States::SYMBOL;
        //covers unprocessable cases too
    }
    //other valid symbols are ignored (spaces etc)
}

void Lexer::minus(char character) 
{
    if (isdigit(character)) {
        _buffer.push_back(character);
        _state = States::INTEGER_PART;
    }
    else if (isSpecialSymbol('-')) {
        _state = States::SYMBOL;
        process(character);
    }
    else {
        _state = States::UNPROCESSABLE;
        process(character);
    }
}

void Lexer::integer_part(char character) 
{
    if (character == '.') {
        _buffer.push_back(character);
        _state = States::FRACTIONAL_PART;
    }
    else if (isdigit(character)) {
        _buffer.push_back(character);
    }
    else {
        _result.emplace_back(std::stod(_buffer));
        _buffer = "";
        _state = States::PENDING;
        process(character);
    }
}

void Lexer::fractional_part(char character) 
{
    if (isdigit(character)) {
        _buffer.push_back(character);
    }
    else {
        _result.emplace_back(std::stod(_buffer));
        _buffer = "";
        _state = States::PENDING;
        process(character);
    }
}

void Lexer::symbol(char character) 
{
    if (Function::isFunction(_buffer)) {
        _result.emplace_back(Token::Types::OPERATOR, _buffer);
        _buffer = "";
        _state = States::PENDING;
    }
    else {
        _state = States::UNPROCESSABLE;
    }
    process(character);
}

void Lexer::word(char character) 
{
    if (isInWord(character)) {
        _buffer.push_back(character);
    }
    else {
        if (Function::isFunction(_buffer))
            _result.emplace_back(Token::Types::OPERATOR, _buffer);
        else
            _result.emplace_back(Token::Types::OPERAND, _buffer);

        _buffer = "";
        _state = States::PENDING;
        process(character);
    }
}

void Lexer::bracket(char character) 
{
    _result.emplace_back(Token::Types::BRACKET, _buffer);
    _buffer = "";
    _state = States::PENDING;
    process(character);
}

void Lexer::matrix(char character) 
{
    if (character == ']') {
        _result.emplace_back(stringToMatrix(_buffer));
        _buffer = "";
        _state = States::PENDING;
    }
    else {
        _buffer.push_back(character);
    }
}

void Lexer::unprocessable(char character) 
{
    if (_ignore_unprocessable) {
        _buffer = "";
        _state = States::PENDING;
        process(character);
    }
    else {
        throw std::runtime_error("parser: invalid sequence < " + _buffer + " >");
    }
}