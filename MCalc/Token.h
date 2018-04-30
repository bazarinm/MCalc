#pragma once
class Token
{
public:
    enum Type {OPERATOR, OPERAND};
    virtual ~Token() = default;

    Type getType() const;
protected:
    Token(Type);
private:
    Type _type;
};

