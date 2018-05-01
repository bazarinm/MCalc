#ifndef TEMP_FSM_H
#define TEMP_FSM_H

#include "Token.h"
#include <vector>
#include <string>

class FSM 
{
public:
    enum States {
        PENDING, MINUS,
        INTEGER_PART,
        FRACTIONAL_PART,
        _OPERATOR, WORD,
        BRACKET, MATRIX,
    };

    FSM();

    void process(const std::string&);

    std::vector<Token> getResult() const;
private:
    States _state;
    std::string _buffer;
    std::vector<Token> _result;

    void pending(const std::string&);

    void minus(const std::string&);
    void integer_part(const std::string&);
    void fractional_part(const std::string&);
    void _operator(const std::string&);
    void word(const std::string&);
    void bracket(const std::string&);
    void matrix(const std::string&);

    bool isDigit(const std::string&);
    bool isAlpha(const std::string&);
    bool isBracket(const std::string&);

    void endOfStr();
};

#endif //TEMP_FSM_H
