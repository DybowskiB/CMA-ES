#include "./algorithm/cmaes.h"
#include "./generators/mersenne_twister/mersenne_twister.h"
#include "./generators/linear_congruential/linear_congruential_generator.h"
#include "./generators/xoroshiro/xoroshiro.h"
#include "./newmat11/newmat.h"
#include "./newmat11/newmatio.h"
#include "./newmat11/newmatap.h"

#include <iostream>
#include <vector>
#include <cmath>

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
    LinearCongruentialGenerator lcg(5ULL);
    MersenneTwister mt(5ULL);
    Xoroshiro xoro(5ULL);

    for (int i = 0; i < 100; ++i)
    {
        cout << "LCG: " << lcg.generate(-10, 10) << " MT: " << mt.generate(-10, 10) << " Xoro: " << xoro.generate(-10, 10) << endl;
    }

    return 0;
}

