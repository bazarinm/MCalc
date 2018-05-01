#include "FSM.h"
#include "Matrix.h"
#include "Function.h"
#include "Operator.h"
#include "Operand.h"
#include <iostream>
#include <vector>
#include <string>

std::ostream& operator<<(std::ostream& o, const Matrix& m) {
    Dimension size = m.getSize();
    for (std::size_t i = 0; i < size._rows; ++i) {
        for (std::size_t j = 0; j < size._columns; ++j)
            o << m.at(i, j) << " ";
        std::cout << std::endl;
    }

    return o;
}

std::ostream& operator<<(std::ostream& o, const Token& t) {
    o << t.getName();

    return o;
}

std::ostream& operator<<(std::ostream& o, Variable& v) {
    switch (v.getType()) {
    case Variable::MATRIX:
        o << v.matrix();
        break;
    case Variable::SCALAR:
        o << v.scalar();
        break;
    }

    return o;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T>& v) {
    for (T& el : v)
        std::cout << el << ", ";

    return o;
}

std::vector<Token> tokenize(const std::string& str) {
    FSM parsing_machine;

    for (auto ch : str)
        parsing_machine.process(std::string(1, ch));

    return parsing_machine.getResult();
}

int main() {
    Variable::newVariable("ab", 2);
    Variable::newVariable("v", Matrix(IDENTITY, 3));
    Variable::newVariable("C", Matrix(IDENTITY, 4));
    std::vector<Token> tokens = tokenize("ab + v - 2 * 3 / det(C) ");
    for (Token& token : tokens)
        std::cout << token << ", ";

    std::cin.get();
    return 0;
}