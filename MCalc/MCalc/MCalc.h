#ifndef MCALC_H
#define MCALC_H

#include "./Matrix/Matrix.h"
#include "./Entities/Variable.h"
#include <iostream>
#include <string>

namespace {
    std::ostream& operator<<(std::ostream& o, const Matrix& m);
    std::ostream& operator<<(std::ostream& o, const Variable& v);

    bool isBadInput(const std::string&);
}

namespace MCalc {
    void repl();
}

#endif