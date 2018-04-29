#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include <functional>
#include <vector>
#include <string>

class Function
{
public:
    Function(std::string);
    
    Variable operator()(std::vector<Variable&>) const;
private:
    std::function<Variable(std::vector<Variable&>)> _function;
    std::vector<Variable::Type> _argument_types; //left to right
    Variable::Type _return_type;
    unsigned _priority;
    unsigned _arity;
};

#endif

