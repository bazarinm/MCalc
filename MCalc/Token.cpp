#include "Token.h"

Token::Token(Type type) : _type(type), _name("%NONAME%") {}

Token::Token(Type type, const std::string& name): _type(type), _name(name) {}

Token::Type Token::getType() const {
    return _type;
}

std::string Token::getName() const {
    return _name;
}
