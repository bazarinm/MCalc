# Matrix calculator

Command line tool for working with matrices. Parses an input for variables, function calls, operators, and evaluates the expression. 
Parser uses finite-state machine to tokenize the input, then the shunting-yard algorithm is used for evaluation.

***
## Installation

1) git clone
2) compile

## Usage

To initialize a matrix, put numbers inside square brackets with each row separated by ";". For example, [1.2 2 -3.1; -3 4.2 5] is a 2x3 matrix.

To assign expression result to a variable, type its name and use "=" symbol before an expression.  
Variable name should contain only alphabetic characters and numbers and begin only with a character or a "_" symbol.   
Variables can be defined and redefined inline and are able to store both scalars and matrices.  

In addition to arithmetic operators, some functions are available:  
"'" -- transpose of a matrix.  
rand (m n) -- creates a random m by n matrice.  
eye (n) -- create an n by n identity matrix  
diag (vector) -- creates a diagonal matrix with entries from a vector (1 by n matrix).  
det/inv (matrix) -- compute a determinant/inverse of a matrix.   
at (matrix, r, c) -- get a number from rth row and cth column of the matrix.  
least (points, degree) -- compute the best approximation by a polinomial of a given degree for a set of points. Uses least squares algorithm. "points" should be a 2 by n matrix (so each column represents a point).  
and others...  

## Examples

1) A = [1 2; 3 4]
2) m = det (3 * (a = rand 3 3))
3) least ([1 2 3; 4 5 6] 2)
4) a = 5 + 6 * (b = 3)
5) 2 + 2
