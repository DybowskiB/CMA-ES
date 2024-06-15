#include <iostream>
#include <vector>
#include <cmath>
#include "./algorithm/cmaes.h"
#include "./generators/mersenne_twister.h"

using namespace std;

// Destination function (Rastrigin function)
double rastrigin(const vector<double>& x) {
    double result = 10 * x.size();
    for (double xi : x) {
        result += xi * xi - 10 * cos(2 * M_PI * xi);
    }
    return result;
}

int main()
{
    int n = 10; // Number of variables
    int lambda = 100; // Population size
    double sigma = 0.5; // Initial standard deviation
    std::vector<double> initial_mean(n, 5.0); // Initial mean vector

    // Create std random number generator
    MersenneTwister rng(1234);

    // Create an instance of CMAES
    CMAES cmaes(n, lambda, sigma, initial_mean, rng);

    // Optimize the Rastrigin function
    std::vector<double> result = cmaes.optimize(1000, rastrigin);

    // Print the result
    std::cout << "Optimal solution: ";
    for (double x : result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

