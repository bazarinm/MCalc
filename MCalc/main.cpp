#include "MCalc.h"
#include <exception>
#include <iostream>

int main() 
{
    try {
        MCalc::repl();
    }
    catch (const std::exception& err) {
        std::cerr << "Program error: " << err.what();
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception occured";
        return -1;
    }

    return 0;
}