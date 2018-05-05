#include "MCalc.h"

#include "Matrix.h"
#include "Variable.h"
#include "shunting-yard.h"
#include "tokenize.h"
#include "Evaluate.h"

namespace {

    std::ostream& operator<<(std::ostream& o, const Matrix& m) 
    {
        const double EPSILON = 1E-4;
        o.precision(4);

        Matrix::Dimensions size = m.getSize();
        for (std::size_t i = 0; i < size.rows; ++i) {
            for (std::size_t j = 0; j < size.columns; ++j)
                if (m.at(i, j) < EPSILON)
                    o << 0 << " ";
                else
                    o << m.at(i, j) << " ";
            if (i != size.rows - 1)
                std::cout << std::endl;
        }

        return o;
    }

    std::ostream& operator<<(std::ostream& o, const Variable& v) 
    {
        o << v.getName() << " ";

        Matrix M;
        switch (v.getType()) {
        case Variable::MATRIX:
            M = v.getMatrix();

            o << "is a " << M.getSize().rows;
            o << "x" << M.getSize().columns << " matrix: ";
            o << std::endl << v.getMatrix();

            break;
        case Variable::SCALAR:
            o << "= " << v.getScalar();

            break;
        case Variable::VOID:
            o << "is undefined ";

            break;
        }

        return o;
    }

} //anonymous namespace end

void MCalc::repl()
{
    std::string input;
    while (1) {
        std::cout << std::endl << "MCalc>: ";
        std::getline(std::cin, input);
        std::cout << std::endl;

        if (input.empty())
            break;
        try {
            Variable result = evaluate(shuntingYard(tokenize(input)));

            if (result.isExpressionResult()) {
                Variable::assign("ans", result);
                std::cout << Variable("ans");
            }
            else
                std::cout << result;
            std::cout << std::endl;
        }

        catch (const parsingError& err) {
            std::cout << "Parsing error: " << err.what();
        }
        catch (const sortingError& err) {
            std::cout << "Sorting error: " << err.what();
        }
        catch (const evaluationError& err) {
            std::cout << "Evaluation error: " << err.what();
        }
        catch (const std::runtime_error& err) {
            std::cout << "Fatal error: " << err.what();
            std::cin.get();
            break;
        }

    }
} 
