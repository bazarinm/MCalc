#include "Matrix.h"
#include <iostream>
int main() {
	Matrix<double> A({ {1, 0, 1}, { 0, 4, 3 }, {0, 2, 0}});
	std::cout << A.determinant();
	//C.display();
	std::cin.get();
}