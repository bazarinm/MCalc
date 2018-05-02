#include "Token.h"

#include "Variable.h"
#include "Function.h"

Token::Token(Types type, const std::string& name): _type(type), _name(name) {
    switch (type) {
    case OPERAND : _variable = Variable(name); break;
    case OPERATOR : _function = Function(name); break;
    case BRACKET : 
        if (name != ")" && name != "(")
            throw std::runtime_error(_name + " is not a bracket");
    }
}

Token::Token(const Variable& v) : _type(OPERAND), _variable(v), _name(v.getName()) {}

Token::Token(const Function& f) : _type(OPERATOR), _function(f), _name(f.getName()) {}

Token::Types Token::getType() const {
    return _type;
}

std::string Token::getName() const {
    return _name;
}

Variable Token::getVariable() const {
    if (_type == OPERAND)
        return _variable;
    else
        throw std::runtime_error("token" + _name + "is not a function");
}

Function Token::getFunction() const
{
    if (_type == OPERATOR)
        return _function;
    else
        throw std::runtime_error("token" + _name + "is not a function");
}

Variable Token::invoke(const std::vector<Variable>& arguments) const {
    if (_type == OPERATOR)
        return _function(arguments);
    else
        throw std::runtime_error("token" + _name + "is not a function");
}

bool Token::isOperand() const {
    return _type == OPERAND;
}

bool Token::isOperator() const {
    return _type == OPERATOR;
}

bool Token::isBracket() const {
    return _type == BRACKET;
}

bool Token::isOpenBracket() const {
    return isBracket() && _name == "(";
}

bool Token::isCloseBracket() const {
    return isBracket() && _name == ")";
}

unsigned Token::getArity() const {
    if (_type == OPERATOR)
        return _function.getArity();
    else
        throw std::runtime_error("token" + _name + "is not a function");
}

unsigned Token::getPriority() const {
    if (_type == OPERATOR)
        return _function.getPriority();
    else
        throw std::runtime_error("token" + _name + "is not a function");
}

bool Token::isLeftAssociative() const
{
    bool isLeftAssociative = false;
    if (_type == OPERATOR)
        isLeftAssociative = _function.isLeftAssociative();
    return isLeftAssociative;
}

bool Token::isRightAssociative() const
{
    bool isRightAssociative = false;
    if (_type == OPERATOR)
        isRightAssociative = _function.isRightAssociative();
    return isRightAssociative;
}
