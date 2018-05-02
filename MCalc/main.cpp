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
            o << t.getName() << " is undefined";
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
        catch (const sortingError& err) {
            std::cout << "Sorting error: " << err.what();
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

    return 0;
}