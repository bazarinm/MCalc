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
  string test = "_name+-0.123* +/*aa* ( --1) det( aaa, [...someMatrix...] aaa^^^bbb& &-&2 name123_aaaa-123 eee0.123eee";
  printVec(tokenize(test));

  return 0;
}