#include "./tests/test1/test1.h"

#include <iostream>

#include "./generators/halton/halton_generator.h"
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

    HaltonGenerator halton(2, 1);
    for(int i = 0; i < 100; i++)
    {
        std::uniform_real_distribution<double> distribution(0.0, 10.0);
        std::cout<< distribution(halton) << std::endl;
        //std::cout << halton() << std::endl;
    }

/*
    std::cout << "Choose test number: ";
    std::cin >> testNumber;

    switch (testNumber) {
        case 1:
            Test1::run();
            break;
        default:
            std::cerr << "Nieprawidłowy numer testu. Wybierz 1, 2 lub 3." << std::endl;
            break;
    }*/

    return 0;
}

