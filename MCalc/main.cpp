#include "Tokenize.h"
#include "Matrix.h"
#include "Function.h"
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
	Variable::newVariable("ab", 2);
	Variable::newVariable("v", Matrix(IDENTITY, 3));
	Variable::newVariable("C", Matrix(IDENTITY, 4));
	std::vector<Token> tokens = tokenize("ab + (v -2.23 )+ v * 3 / det(C) 0.123");

	std::cout << tokens;
	std::cin.get();
	return 0;
}