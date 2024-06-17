#include "./algorithm/cmaes.h"
/*#include "./generators/mersenne_twister/mersenne_twister.h"
#include "./generators/linear_congruential/linear_congruential_generator.h"*/
#include "./generators/xoroshiro/xoroshiro.h"
#include "./generators/xoroshiro/int_xoroshiro.h"
#include "./newmat11/newmat.h"
#include "./newmat11/newmatio.h"
#include "./newmat11/newmatap.h"
#include "./test_generator.cpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <random>

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
    MyRandomEngine myRand;
    Xoroshiro xoro(12345);
    IntXoroshiro int_xoro(12345);
    std::uniform_real_distribution<double> dist1;
    std::normal_distribution<double> dist2(0.0, 1.0); // use normal
    std::uniform_int_distribution<int> dist3(-5, 5);


    for (int i = 0; i < 100; ++i)
    {
        cout << i << ". " << dist3(int_xoro) << endl;
    }

    return 0;
}

