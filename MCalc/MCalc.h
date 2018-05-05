#ifndef MCALC_H
#define MCALC_H

#include "Matrix.h"
#include "Variable.h"
#include <iostream>

namespace {
    std::ostream& operator<<(std::ostream& o, const Matrix& m);
    std::ostream& operator<<(std::ostream& o, const Variable& v);
}

namespace MCalc {
    void repl();
}

#endif