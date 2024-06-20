#include "./tests/test1/test1.h"
#include "./tests/test2/test2.h"

#include <iostream>
#include <random>

using namespace std;

// Destination function (Rastrigin function)
/*double rastrigin(const RowVector& x)
{
    double result = 10 * x.size();
    cout << "Ncols: " << x.ncols();
    for (int i = 0; i < x.ncols(); ++i)
    {
        result += x.element(i) * x.element(i) - 10 * cos(2 * M_PI * x.element(i));
    }
    return result;
}

double fitness(const RowVector& x)
{
    return (100 * sqrt(abs(x.element(1) - 0.01 * pow(x.element(0), 2))) + 0.01 * abs(x.element(0) + 10));
}*/

int main()
{
    int testNumber;

    std::cout << "Tests: " << std::endl;
    std::cout << "1. Generators tests (histogram data + phi-square test)." << std::endl;
    std::cout << "2. CMAES tests (ECDF data)." << std::endl;
    std::cout << "Choose test number: " << std::endl;
    std::cin >> testNumber;

    switch (testNumber) {
        case 1:
            Test1::run();
            break;
        case 2:
            Test2::run();
            break;
        default:
            std::cerr << "Incorrect test number choose 1 or 2." << std::endl;
            break;
    }

    return 0;
}

