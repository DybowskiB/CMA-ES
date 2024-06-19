#include "./algorithm/cmaes.h"
#include "./generators/mersenne_twister/mersenne_twister_generator.h"
#include "./generators/linear_congruential/linear_congruential_generator.h"
#include "./generators/xoroshiro/xoroshiro_generator.h"
#include "./generators/halton/halton_generator.h"
#include "./generators/lagged_fibonacci/lagged_fibonacci_generator.h"
#include "./generators/chacha20/chacha20.h"
#include "./newmat11/newmat.h"
#include "./newmat11/newmatio.h"
#include "./newmat11/newmatap.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <climits>

using namespace std;

// Destination function (Rastrigin function)
double rastrigin(const RowVector& x)
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
}

int main()
{
    MersenneTwisterGenerator mt(12345);
    CMAES cmaes(20, 2, mt);
    cmaes.optimize(100000, 0.001, fitness);

    return 0;
}

