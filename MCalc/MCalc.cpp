#include "MCalc.h"

#include "Entities/Matrix/Matrix.h"
#include "Entities/Variable.h"
#include "Parser/algorithms.h"
#include <stdexcept>
#include <iostream>
#include <string>

namespace {

    std::ostream& operator<<(std::ostream& o, const Matrix& m) 
    {
        Matrix::Dimensions size = m.getSize();
        for (std::size_t i = 0; i < size.rows; ++i) {
            for (std::size_t j = 0; j < size.columns; ++j) {
                if (m.at(i, j) >= 0)
                    o << " ";
                o << m.at(i, j) << " ";
            }
            if (i != size.rows - 1)
                std::cout << std::endl;
        }

        return o;
    }

    std::ostream& operator<<(std::ostream& o, const Variable& v) 
    {
        o << v.getName();

        Matrix M;
        switch (v.getType()) {
        case Variable::Types::MATRIX:

            M = v.getMatrix();
            o << " is a " << M.getSize().rows;
            o << " by " << M.getSize().columns; 
            o << " matrix: ";
            o << std::endl << M;

            break;
        case Variable::Types::SCALAR:

            o << " = " << v.getScalar();

            break;
        case Variable::Types::VOID:

            o << " is undefined ";

            break;
        }

        return o;
    }

    bool isBadInput(const std::string& input) {
        bool bad_input = false;
        for (char c : input)
            if (c < 0 || c > 128) {
                bad_input = true;
                break;
            }

        return bad_input;
    }

} //anonymous namespace end

void MCalc::repl()
{
    std::cout.precision(4);
    std::cout << std::fixed;

    std::string input;
    while (1) {
        std::cout << std::endl << "MCalc>: ";
        std::getline(std::cin, input);
        std::cout << std::endl;

        if (input.empty())
            break;
        if (isBadInput(input)) {
            std::cout << "Input error: non-ascii characters in the input";
            continue;
        }

        try {
            using namespace ShuntingYard;
            Variable result = evaluate(sort(tokenize(input)));

            if (result.isAssignmentResult())
                std::cout << result;
            else {
                std::cout << Variable::assign("ans", result);
            }

            std::cout << std::endl;
        }
        catch (const ExecutionError& err) {
            std::cout << "Error: " << err.what();
        }
        catch (const std::runtime_error& err) {
            std::cout << "Program error: " << err.what();
            std::cout << std::endl << "Wait for bugfixes";
        }

    }
} 
