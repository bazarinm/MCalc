#ifndef VARIABLE_H 
#define VARIABLE_H

#include "../Matrix/Matrix.h"
#include <string>
#include <map>

class Variable {
public:
    enum Types { MATRIX, SCALAR, VOID };

    Variable();
    Variable(const Matrix&);
    Variable(double);
    Variable(const std::string&);

    Types getType() const;
    std::string getName() const;
    Matrix getMatrix() const;
    double getScalar() const;
    bool isAssignmentResult() const;

    static Variable assign(const std::string& name, const Variable&);

    static bool isVariable(const std::string&);
private:
    Types _type;
    std::string _name;
    Matrix _matrix;
    double _scalar;

    static std::string constant_name;
    static std::map<std::string, Variable> _variables;
};

#endif
