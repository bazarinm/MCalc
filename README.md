# Matrix calculator

Command line tool for working with matrices. Parses input for variables, function calls and operators, then evaluates the result. 
Parser is a combination of a finite-state machine and the shunting-yard algorithm.
***
## Installation

1) git clone
2) compile

## Usage
To initialize a matrix, put numbers inside square brackets with each row separated by ";". For example, [1.2 2 -3.1; -3 4.2 5] is a 2x3 matrix.

To assign expression result to a variable, type its name and use "=" symbol before an expression.
Variable name should contain only alphabetic characters and numbers and start olby with a character or a "_" symbol. 
Variables can be defined and redefined inline and are able to store both scalars and matrices.

In addition to arithmetic operators, some functions are available:
"'" -- transpose of a matrix.
rand (m n) -- creates a random m by n matrice.
det/inv (matrix) -- compute determinant/inverse of a matrix. 
at (matrix, r, c) -- get a number from rth row and cth column of the matrix.
least (points, degree) -- compute the best approximation by polinomial of given set of points and degree. Uses least squares algorithm. "points" should be a 2 by n matrix (so each column represents a point).

## Examples
1) A = [1 2; 3 4]
2) m = det (3 * (a = rand 3 3))
3) least ([1 2 3; 4 5 6] 2)
4) a = 5 + 6 * (b = 3)
5) 2 + 2
