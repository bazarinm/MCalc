#include "Matrix.h"
#include "Function.h"
#include <iostream>

int main() {

	Matrix A(IDENTITY, 6);
	Matrix B(UPPER_TRIANGLE, 3, {1, 2, 3, 4, 5, 6});
	Matrix C(LOWER_TRIANGLE, 3, { 1, 2, 3, 4, 5, 6 });
	Matrix D(SYMMETRIC, 3, { 1, 2, 3, 4, 5, 6 });

	A.display();
	std::cout << std::endl;
	B.display();
	std::cout << std::endl;
	C.display();
	std::cout << std::endl;
	D.display();
	std::cout << std::endl;

	(B*C).display();
	std::cout << std::endl;
	((B*C) + Matrix(IDENTITY, 3)).display();
	std::cout << std::endl;
	std::cout << B.determinant() << std::endl;
	std::cout << C.determinant() << std::endl;
	std::cout << (B * C).determinant() << std::endl;

    Function det("det");
    Function add("+");

    std::cout << det({ B }).scalar() << std::endl;
    std::cout << add({ 1.8, 2.3 }).scalar() << std::endl;
    add({ B, C }).matrix().display();

	std::cin.get();
}