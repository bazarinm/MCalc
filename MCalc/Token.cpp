#include "Token.h"

Token::Token(Types type) : _type(type), _name("%NONAME%") {}

Token::Token(Types type, const std::string& name): _type(type), _name(name) {}

Token::Types Token::getType() const {
    return _type;
}

std::string Token::getName() const {
    return _name;
}
