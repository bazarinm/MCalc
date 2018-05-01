#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Types {OPERATOR, OPERAND};

    virtual ~Token() = default;

    Types getType() const;
    std::string getName() const;
protected:
    Token(Types);
    Token(Types, const std::string&);
private:
    Types _type;
    std::string _name;
};

#endif

