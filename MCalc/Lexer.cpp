#include "Lexer.h"

#include "Function.h"
#include "Token.h"
#include "Matrix.h"
#include <vector>
#include <string>
#include <regex>
#include <cctype>

Lexer::Lexer() : _state(PENDING) 
{
}

std::vector<Token> Lexer::getResult() const {
    return _result;
};

bool Lexer::isNumber(const std::string& str) const {
    return std::regex_match(str, std::regex("[-]?[0-9]+[.]?[0-9]*"));
}

/* symbols that does not fit into any category */
bool Lexer::isUnprocessable(char character) {
    return !(0
        || isMinus(character)
        || std::isspace(character)
        || std::isdigit(character)
        || isWordStart(character)
        || isInWord(character)
        || isRoundBracket(character)
        || isSquareBracket(character)
        || isSpecialSymbol(character)
        );
}

bool Lexer::isMinus(char character) {
    return character == '-';
}

bool Lexer::isWordStart(char character) {
    return std::isalpha(character) || character == '_';
}


bool Lexer::isInWord(char character) {
    return isWordStart(character) || std::isdigit(character);
}

/* any special symbols that correspond to a function */
bool Lexer::isSpecialSymbol(char character) {
    return 1 
        && !std::isspace(character)
        && !std::isdigit(character)
        && !isWordStart(character)
        && !isInWord(character)
        && !isRoundBracket(character)
        && !isSquareBracket(character)
        && Function::isFunction(std::string(1, character)) 
        ;
}

bool Lexer::isRoundBracket(char character) {
    return character == '(' || character == ')';
}


bool Lexer::isSquareBracket(char character) {
    return character == '[' || character == ']';
}

void Lexer::endOfInput() {
    process('\n');
}

Matrix Lexer::stringToMatrix(const std::string& matrixString) 
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
                    throw parsingError("parser: incorrect symbol < " + buffer + " > in matrix initialization");

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
                throw parsingError("parser: incorrect symbol < " + buffer + " > in matrix initialization");

            buffer = "";
            pending = true;
        }
        if (!bufferRow.empty()) {
            matrixVector.push_back(bufferRow);
        }
    }

    try { 
        return Matrix(matrixVector); 
    }
    catch (std::runtime_error err) { 
        throw parsingError(err.what()); 
    }
};

void Lexer::process(char character) 
{
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

void Lexer::pending(char character) 
{
    if (isMinus(character)) {
        _buffer.push_back(character);
        _state = MINUS;
    }
    else if (std::isdigit(character)) {
        _buffer.push_back(character);
        _state = INTEGER_PART;
    }
    else if (isWordStart(character)) {
        _buffer.push_back(character);
        _state = WORD;
    }
    else if (isRoundBracket(character)) {
        _buffer.push_back(character);
        _state = BRACKET;
    }
    else if (character == '[') {
        // _buffer.push_back(character);
        _state = MATRIX;
    }
    else if (isSpecialSymbol(character)) {
        _buffer.push_back(character);
        _state = SYMBOL;
    }
    else if (isUnprocessable(character)) {
        _buffer.push_back(character);
        _state = UNPROCESSABLE;
    }
    //other valid symbols are ignored (spaces etc)
}

void Lexer::minus(char character) 
{
    if (isdigit(character)) {
        _buffer.push_back(character);
        _state = INTEGER_PART;
    }
    else if (isSpecialSymbol('-')) {
        _state = SYMBOL;
        process(character);
    }
    else {
        _state = UNPROCESSABLE;
        process(character);
    }
}

void Lexer::integer_part(char character) 
{
    if (character == '.') {
        _buffer.push_back(character);
        _state = FRACTIONAL_PART;
    }
    else if (isdigit(character)) {
        _buffer.push_back(character);
    }
    else {
        _result.emplace_back(std::stod(_buffer));
        _buffer = "";
        _state = PENDING;
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
        _state = PENDING;
        process(character);
    }
}

void Lexer::symbol(char character) 
{
    _result.emplace_back(Token::OPERATOR, _buffer);
    _buffer = "";
    _state = PENDING;
    process(character);
}

void Lexer::word(char character) 
{
    if (isInWord(character)) {
        _buffer.push_back(character);
    }
    else {
        if (Function::isFunction(_buffer))
            _result.emplace_back(Token::OPERATOR, _buffer);
        else
            _result.emplace_back(Token::OPERAND, _buffer);

        _buffer = "";
        _state = PENDING;
        process(character);
    }
}

void Lexer::bracket(char character) 
{
    _result.emplace_back(Token::BRACKET, _buffer);
    _buffer = "";
    _state = PENDING;
    process(character);
}

void Lexer::matrix(char character) 
{
    if (character == ']') {
        _result.emplace_back(stringToMatrix(_buffer));
        _buffer = "";
        _state = PENDING;
    }
    else {
        _buffer.push_back(character);
    }
}

void Lexer::unprocessable(char character) 
{
    if (isUnprocessable(character)) {
        _buffer.push_back(character);
    } 
    else {
        //process(character) //<-- uncomment this in case its ok to ignore unprocessable symbols
        //_buffer = "";
        //_state = PENDING;
        throw parsingError("parser: invalid sequence < " + _buffer + " >");
    }
}