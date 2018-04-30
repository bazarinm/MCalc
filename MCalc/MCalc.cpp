#include "MCalc.h"

#include "FSM.h"
#include "Token.h"
#include "Operator.h"
#include "Operand.h"

MCalc::MCalc()
{
}

void MCalc::start() {

}

std::vector<Token> MCalc::tokenize(std::string& input) {
    FSM parsing_machine;

    for (auto ch : input) {
        parsing_machine.process(ch);
    }
    parsing_machine.endOfStr();

    std::vector<Token> tokens;
    for (std::string& name : parsing_machine.getResult()) {
        if (isVariable(name))
            tokens.push_back(Operand(_variables[name]));
    }
    return tokens;
}
