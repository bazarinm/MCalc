#include "FSM.h"
#include "Matrix.h"
#include "Function.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

std::ostream& operator<<(std::ostream& o, const Matrix& m) {
    Dimension size = m.getSize();
    for (std::size_t i = 0; i < size._rows; ++i) {
        for (std::size_t j = 0; j < size._columns; ++j)
            o << m.at(i, j) << " ";
        if (i != size._rows - 1)
            std::cout << std::endl;
    }

    return o;
}

std::ostream& operator<<(std::ostream& o, const Token& t) {
    o << t.getName();
    if (t.isOperand()) {
        o << " = ";
        switch (t.getVariable().getType()) {
        case Variable::MATRIX:
            o << std::endl << t.getVariable().getMatrix();
            break;
        case Variable::SCALAR:
            o << t.getVariable().getScalar();
            break;
        }
    }
    else if (t.isOperator())
        o << " is a function ";

    return o;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& v) {
    for (const T& el : v)
        std::cout << std::endl << el << std::endl;

    return o;
}

std::vector<Token> tokenize(const std::string& str) {
    FSM parsing_machine;

    for (char ch : str)
        parsing_machine.process(std::string(1, ch));
    parsing_machine.endOfStr();

    return parsing_machine.getResult();
}

int main() {
    Variable::assign("ab", 2);
    Variable::assign("v", Matrix(IDENTITY, 3));
    Variable::assign("C", Matrix(IDENTITY, 4));
    std::vector<Token> tokens = tokenize("ab + (v -2 )+ v * 3 / det(C) ");

    std::cout << tokens;

    std::cin.get();
    return 0;
}