#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include <functional>
#include <vector>
#include <map>
#include <string>

class Function
{
public:
    Function(std::string);
    
    Variable operator()(std::vector<Variable>);
private:
    std::map<
        std::vector<Variable::Type>, //left to right
        std::function<Variable(std::vector<Variable>)>
    > _function;

    std::map<
        std::vector<Variable::Type>, //left to right
        bool
    > _argument_types; 

    Variable::Type _return_type;
    unsigned _priority;
};

#endif

