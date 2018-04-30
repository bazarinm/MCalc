#include "Matrix.h"
#include "Function.h"
#include <iostream>

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

int main() {

	//Matrix A(IDENTITY, 6);
	//Matrix B(UPPER_TRIANGLE, 3, {1, 2, 3, 4, 5, 6});
	//Matrix C(LOWER_TRIANGLE, 3, { 1, 2, 3, 4, 5, 6 });
	//Matrix D(SYMMETRIC, 3, { 1, 2, 3, 4, 5, 6 });

	//A.display();
	//std::cout << std::endl;
	//B.display();
	//std::cout << std::endl;
	//C.display();
	//std::cout << std::endl;
	//D.display();
	//std::cout << std::endl;

	//(B*C).display();
	//std::cout << std::endl;
	//((B*C) + Matrix(IDENTITY, 3)).display();
	//std::cout << std::endl;
	//std::cout << B.determinant() << std::endl;
	//std::cout << C.determinant() << std::endl;
	//std::cout << (B * C).determinant() << std::endl;

    Variable A = Matrix({ 2, 3 }, { 1, 2, 3, 4, 5, 6 });
    Variable B = 3;

    Function product("*");

    std::cout << product({ A, B }) << std::endl;

    B = Matrix({ 3, 2 }, { 1, 2, 3, 4, 5, 6 });

    std::cout << product({ A, B }) << std::endl;
    
	std::cin.get();
}