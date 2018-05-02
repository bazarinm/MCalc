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
        if (i != size._rows - 1)
            std::cout << std::endl;
    }

    return o;
}

std::ostream& operator<<(std::ostream& o, const Token& t) {
    if (t.isOperand()) {
        switch (t.getVariable().getType()) {
        case Variable::MATRIX:
            o << t.getName() << " = ";
            o << std::endl << t.getVariable().getMatrix();
            break;
        case Variable::SCALAR:
            o << t.getName() << " = ";
            o << t.getVariable().getScalar();
            break;
        case Variable::VOID:
            o << t.getName() << " is undefuned";
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
    Matrix A(UPPER_TRIANGLE, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix B({ 3, 3 }, { 4, 3, 1, 0, -2, 11, -4, 5, 7 });
    Matrix C({ 2, 4 }, { 2, 1, 7, 3, 1.8, 1, -2, -1 });
    Matrix D({ 8, 1 }, { 1, 0, 1, 0, 1, 0, 1, 0 });

    Variable::assign("A", A);
    Variable::assign("B", B);
    Variable::assign("C", C);
    Variable::assign("D", D);
    Variable::assign("ans", 0);

    std::string input;
    while (1) {
        std::cout << std::endl << "MCalc>: ";
        std::getline(std::cin, input);
        if (input.empty())
            break;
        try {
            std::cout << std::endl << evaluate(shuntingYard(tokenize(input)));
        }

        catch (const parsingError& err) {
            std::cout << "Parsing error: " << err.what();
        }
        catch (const evaluationError& err) {
            std::cout << "Evaluation error: " << err.what();
        }
        catch (const std::runtime_error& err) {
            std::cout << "Fatal error: " << err.what();
            std::cin.get();
            break;
        }

        std::cout << std::endl;
    }

    //std::cin.get();
    return 0;
}