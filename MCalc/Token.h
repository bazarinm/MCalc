#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Type {OPERATOR, OPERAND};

    virtual ~Token() = default;

    Type getType() const;
    std::string getName() const;
protected:
    Token(Type);
    Token(Type, const std::string&);
private:
    Type _type;
    std::string _name;
};

#endif

