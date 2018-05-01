#ifndef TOKEN_H
#define TOKEN_H

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

#endif

