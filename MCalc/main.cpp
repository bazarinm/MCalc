#include "tokenize.h"
#include "Matrix.h"
#include "Function.h"
#include "shunting-yard.h"
#include "Evaluate.h"
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

int main() {
    Matrix ab(UPPER_TRIANGLE, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix CvG({ 3, 3 }, { 4, 3, 1, 0, -2, 11, -4, 5, 7 });
    double aY = 3;
    double _UU = 2;

    Variable::assign("ab", ab);
    Variable::assign("CvG", CvG);
    Variable::assign("aY", aY);
    Variable::assign("_UU", _UU);

    std::string input;
    while (1) {
        std::cout << std::endl << "> ";
        std::getline(std::cin, input);
        if (input.empty())
            break;
        std::cout << evaluate(shunting_yard(tokenize(input)));
    }

    //std::cin.get();
    return 0;
}