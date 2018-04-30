#include "FSM.h"
#include "Matrix.h"
#include "Function.h"
#include "Operator.h"
#include "Operand.h"
#include <iostream>
#include <vector>
#include <string>

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

template <typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T>& v) {
    for (T& el : v)
        std::cout << el << ", ";

    return o;
}


std::vector<std::string> tokenize(std::string str) {

}

int main() {
  std::string test = "3.32 * 2.87";
  std::vector<std::string> str = tokenize(test);

  std::vector<Token*> tokens;

  for (std::string& c : str)
      if (c == "+" || c == "*")
          tokens.push_back(new Operator(c));
      else
          tokens.push_back(new Operand(std::stod(c)));
    
  std::cout << dynamic_cast<Operator*>(tokens[1])->invoke(
      {
          dynamic_cast<Operand*>(tokens[0])->getVariable(),
          dynamic_cast<Operand*>(tokens[2])->getVariable()
      }
  );

  for (Token* t : tokens)
      delete(t);

  std::cin.get();
  return 0;
}