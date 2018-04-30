#ifndef DATABASE_H
#define DATABASE_H

#include "Variable.h"
#include <functional>
#include <string>
#include <vector>
#include <map>

struct FunctionInfo {
    enum InvocationType { FUNCTION, OPERATOR };
    enum AccotiativityType { LEFT, RIGHT, BOTH };

    unsigned _arity;
    unsigned _priority;
    InvocationType _invocation;
    AccotiativityType _associativity;

    std::vector<std::vector<Variable::Type>> _parameters;
    std::map<
        std::vector<Variable::Type>, //left to right
        std::function<Variable(std::vector<Variable>)>
    > _function;
};

//std::map<std::string, FunctionInfo> database = {
//    { 
//        //name = 
//        "*",
//        {
//            //arity = 
//            2,
//            //priority = 
//            2,
//            //invocation = 
//            FunctionInfo::OPERATOR,
//            //associativity = 
//            FunctionInfo::BOTH,
//            //parameters = 
//            std::vector<std::vector<Variable::Type>>
//            ({
//                { Variable::MATRIX, Variable::MATRIX },
//                { Variable::SCALAR, Variable::SCALAR },
//                { Variable::MATRIX, Variable::SCALAR },
//                { Variable::SCALAR, Variable::MATRIX }
//            }),
//            //functions:
//
//            std::map<std::vector<Variable::Type>, std::function<Variable(std::vector<Variable>)>>
//            ({
//                {
//                    { Variable::MATRIX, Variable::MATRIX },
//                    [](std::vector<Variable> args) -> Variable { return args[0].matrix() * args[1].matrix(); }
//                }
//            })
//        }
//    }
//}


#endif
