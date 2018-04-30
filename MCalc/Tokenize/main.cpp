#include <iostream>
#include <vector>
#include <string>
#include "FSM.h"

using namespace std;


template<typename T>
void printVec(vector<T> vec) {
  cout << "[";
  for (auto el : vec) {
    cout << el << ", ";
  }

  cout << "]" << endl;
}


vector<string> tokenize(string str) {
  FSM fsm;

  for (auto ch : str) {
    fsm.process(ch);
  }
  fsm.endOfStr();

  return fsm.getResult();
}


int main() {
  int aaa222aaa = 1;
  vector<string> vec = tokenize("___-0.16*-4p.+..1oa_AAeu-23.234a_o ...++....e oea-u /  ^^^&&&& -0.aaa 4aoe   uo-aeu213oe");
  printVec(vec);
  printVec(tokenize("det(matrixName)"));
  printVec(tokenize("det([ ...matrix...])"));

  return 0;
}