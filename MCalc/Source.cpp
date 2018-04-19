#include "Matrix.h"
#include <iostream>
int main() {
	Matrix<double> A({ {1, 5, 1}, { 7, 4, 3 }, {-3, 2, -5}});
	(A / A).display();

	std::cin.get();
}