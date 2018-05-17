#include "Token.h"

#include "./Entities/Variable.h"
#include "./Entities/Function.h"
#include <stdexcept>
#include <vector>
#include <string>

Token::Token(Types type, const std::string& name): _type(type), _name(name) 
{
    switch (_type)
    {
    case Token::OPERATOR:
        if (Function::isFunction(_name))
            _function = Function(_name);
        else
            throw std::runtime_error("token: " + _name + "is not a function ");
        break;
    case Token::OPERAND:
        _variable = Variable(_name);
        break;
    case Token::BRACKET:
        //do nothing
        break;
    }
}

Token::Token(const Variable& v) : _type(OPERAND), _variable(v), _name(v.getName()) 
{
}

Token::Token(const Function& f) : _type(OPERATOR), _function(f), _name(f.getName()) 
{
}

Token::Types Token::getType() const {
    return _type;
}

std::string Token::getName() const {
    return _name;
}

Variable Token::getVariable() const 
{
    if (_type == OPERAND)
        return _variable;
    else
        throw std::runtime_error("token: " + _name + "is not a variable ");
}

Function Token::getFunction() const
{
    if (_type == OPERATOR)
        return _function;
    else
        throw std::runtime_error("token: " + _name + "is not a function ");
}

Variable Token::invoke(const std::vector<Variable>& arguments) const 
{
    if (_type == OPERATOR)
        return _function(arguments);
    else
        throw std::runtime_error("token: " + _name + "is not a function ");
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

unsigned Token::getArity() const 
{
    if (_type == OPERATOR)
        return _function.getArity();
    else
        throw std::runtime_error("token: " + _name + "is not a function ");
}

unsigned Token::getPriority() const 
{
    if (_type == OPERATOR)
        return _function.getPriority();
    else
        throw std::runtime_error("token: " + _name + "is not a function ");
}

bool Token::isLeftAssociative() const
{
    bool isLeftAssociative = false;
    if (_type == OPERATOR)
        isLeftAssociative = _function.isLeftAssociative();
    else
        throw std::runtime_error("token: " + _name + "is not a function ");

    return isLeftAssociative;
}

bool Token::isRightAssociative() const
{
    bool isRightAssociative = false;
    if (_type == OPERATOR)
        isRightAssociative = _function.isRightAssociative();
    else
        throw std::runtime_error("token: " + _name + "is not a function ");

    return isRightAssociative;
}
