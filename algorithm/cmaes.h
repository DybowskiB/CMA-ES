#pragma once

#include <vector>
#include <functional>
#include <random>
#include "../generators/random_number_generator.h"

class CMAES {
public:
    CMAES(int n, int lambda, double sigma, std::vector<double> initial_mean, RandomNumberGenerator& rng_generator);

    std::vector<double> optimize(int max_iterations, std::function<double(const std::vector<double>&)> objective_function);

private:
    int n; // number of variables in the optimization problem
    int lambda; // population size, i.e., the number of generated samples
    double sigma; // initial standard deviation.
    std::vector<double> mean; // vector storing the mean values of variables
    std::vector<double> weights; // vector containing weights assigned to each sample or candidate solution
    std::vector<std::vector<double>> cov_matrix; // matrix representing the covariance matrix of the distribution
    RandomNumberGenerator& rng; // random number generator

    std::vector<std::vector<double>> generate_samples();
    std::vector<std::pair<double, std::vector<double>>> evaluate_samples(const std::vector<std::vector<double>>& samples, std::function<double(const std::vector<double>&)> objective_function);
    void update_distribution(const std::vector<std::pair<double, std::vector<double>>>& evaluated_samples);
};
