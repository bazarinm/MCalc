#ifndef MCALC_H
#define MCALC_H

#include "Entities/Matrix/Matrix.h"
#include "Entities/Variable.h"
#include <iostream>
#include <string>

namespace {
    std::ostream& operator<<(std::ostream&, const Matrix&);
    std::ostream& operator<<(std::ostream&, const Variable&);

    bool isBadInput(const std::string&);
}

namespace MCalc {
    void repl();
}

#endif