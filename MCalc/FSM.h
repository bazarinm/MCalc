#ifndef TEMP_FSM_H
#define TEMP_FSM_H

#include <iostream>
#include <vector>
#include <string>

template <typename T>
bool includes(std::vector<T> coll, T item) {
  for (auto el : coll) {
    if (el == item) {
      return true;
    }
  }

  return false;
}

enum STATE {
  PENDING,
  MINUS,
  INTEGER_PART,
  FRACTIONAL_PART,
  _OPERATOR,
  WORD,
  BRACKET,
  MATRIX,
};


class FSM {
 public:

  STATE state = PENDING;
  std::string buffer;

  std::vector<std::string> result;
  std::vector<std::string> getResult() {
    return result;
  };
  bool isOperator(char ch) {
    std::vector<std::string> operators = {"+", "-", "*", "/"};
    return includes(operators, std::string(1, ch));
  }
  bool isBracket(char ch) {
    return ch == '(' || ch == ')';
  }
  void endOfStr() {
    process('\n');
  }

  void process(char ch) {
    switch (state) {
      case PENDING:
        pending(ch);
        break;
      case MINUS:
        minus(ch);
        break;
      case INTEGER_PART:
        integer_part(ch);
        break;
      case FRACTIONAL_PART:
        fractional_part(ch);
        break;
      case _OPERATOR:
        _operator(ch);
        break;
      case WORD:
        word(ch);
        break;
      case BRACKET:
        bracket(ch);
        break;
      case MATRIX:
        matrix(ch);
        break;
    }
  }

  void pending(char ch) {
    if (ch == '-') {
      buffer.push_back(ch);
      state = MINUS;
    } else if (isOperator(ch)) {
      buffer.push_back(ch);
      state = _OPERATOR;
    } else if (isdigit(ch)) {
      buffer.push_back(ch);
      state = INTEGER_PART;
    } else if (isalpha(ch) || ch == '_') {
      buffer.push_back(ch);
      state = WORD;
    } else if (isBracket(ch)) {
      buffer.push_back(ch);
      state = BRACKET;
    } else if (ch == '[') {
      buffer.push_back(ch);
      state = MATRIX;
    }
  }

  void minus(char ch) {
    if (isdigit(ch)) {
      buffer.push_back(ch);
      state = INTEGER_PART;
    } else {
      result.push_back(buffer);
      buffer = "";
      state = PENDING;
      process(ch);
    }
  }

  void integer_part(char ch) {
    if (ch == '.') {
      buffer.push_back(ch);
      state = FRACTIONAL_PART;
    } else if (isdigit(ch)) {
      buffer.push_back(ch);
    } else {
      result.push_back(buffer);
      buffer = "";
      state = PENDING;
      process(ch);
    }
  }

  void fractional_part(char ch) {
    if (isdigit(ch)) {
      buffer.push_back(ch);
    } else {
      result.push_back(buffer);
      buffer = "";
      state = PENDING;
      process(ch);
    }
  }

  void _operator(char ch) {
    result.push_back(buffer);
    buffer = "";
    state = PENDING;
    process(ch);
  }

  void word(char ch) {
    if (isalnum(ch) || ch == '_') {
      buffer.push_back(ch);
    } else {
      result.push_back(buffer);
      buffer = "";
      state = PENDING;
      process(ch);
    }
  }

  void bracket(char ch) {
    result.push_back(buffer);
    buffer = "";
    state = PENDING;
    process(ch);
  }

  void matrix(char ch) {
    if (ch == ']') {
      buffer.push_back(ch);
      result.push_back(buffer);
      buffer = "";
      state = PENDING;
    } else {
      buffer.push_back(ch);
    }
  }
};

#endif //TEMP_FSM_H
