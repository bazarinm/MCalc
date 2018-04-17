#include "Matrix.h"
#include <iostream>
int main() {
	Matrix<double> A({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, { 10, 11, 12 } });
	Matrix<double> B({3, 4}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
	A.display();
	std::cout << std::endl;
	B.display();
	std::cout << std::endl;
	Matrix<double> C = A * B;
	Matrix<double> D();
	C.display();
	std::cin.get();
}