#include "FSM.h"
#include "Matrix.h"
#include "Function.h"
#include "Operator.h"
#include "Operand.h"
#include <iostream>
#include <vector>
#include <string>

std::ostream& operator<<(std::ostream& o, Matrix& m) {
    Dimension size = m.getSize();
    for (std::size_t i = 0; i < size._rows; ++i) {
        for (std::size_t j = 0; j < size._columns; ++j)
            o << m.at(i, j) << " ";
        std::cout << std::endl;
    }

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


int main() {
    Function mult("*");
    std::cout << mult({ 3, 4 }) << std::endl;
    std::cout << Function::isOperator("*");

    std::cin.get();
    return 0;
}