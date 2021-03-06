# MCalc

Command line application for working with matrices.

Parses an input for variables, function calls, operators, and evaluates the expression.

Parser uses finite-state machine to tokenize the input, then the shunting-yard algorithm is used for evaluation.

***
## Installation

1. git clone
2. compile

***
## Usage

To **initialize** a *matrix*, put numbers inside *square brackets* ```[]``` with each row separated by ```;```.

For example, ```[1.2 2 -3.1; -3 4.2 5]``` is a *2x3 matrix*.

To **assign** expression result to a variable, type its name and use ```=``` symbol before an expression.

**Variable name** should begin only with an ```alphabetic character``` or a ```_``` symbol and contain only ```alphanumeric characters```.
Variables can be defined and redefined inline and are able to store both *scalars* and *matrices*.

### Available functions:
* **Basic arithmetic** operators ```+```, ```-```, ```*```, ```/```, ```^``` work both for *matrices* and *scalars*.
* ```'``` &mdash; **transpose** of a *matrix*.
* ```rand(m n)``` &mdash; creates a **random** *m* by *n* *matrix*.
* ```eye(n)``` &mdash; create an *n* by *n* **identity matrix**.
* ```diag(vector)``` &mdash; creates a **diagonal matrix** with entries from **a vector** *(1 by n matrix)*.
* ```det/inv(matrix)``` &mdash; compute a **determinant/inverse** of a *matrix*.
* ```at(matrix r c)``` &mdash; **get a number** from *rth* row and *cth* column of the *matrix*.
* ```least(points degree)``` &mdash; compute the best **approximation by a polynomial** of a given degree for a set of points. Uses **least squares** algorithm. ```points``` should be a **2 by n matrix** (so each column represents a point).

## Examples
```
MCalc>: A = [1 2 3; 4 5 6] * [1 2 3; 4 5 6]'
MCalc>: m = det (3 * (a = rand 3 3))
MCalc>: least ([1 2 3; 4 5 6] 2)
MCalc>: a = 5 + 6 * (b = 3)
MCalc>: 2 + 2
// and so on
```
