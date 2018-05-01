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
    Variable::newVariable("A", 3);
    Variable::newVariable("B", Matrix(IDENTITY, 3));
    std::cout << mult({ Variable("A"), Variable("B") }) << std::endl;

    Operand op(Matrix({ {1, 2, 3} }));
    std::cout << op.getVariable();

    std::cin.get();
    return 0;
}