#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <functional>
#include "cmaes.h"

using namespace std;


CMAES::CMAES(int n, int lambda, double sigma, vector<double> initial_mean, RandomNumberGenerator& rng_generator)
    : n(n), lambda(lambda), sigma(sigma), mean(initial_mean), rng(rng_generator)
{
    weights = vector<double>(lambda, 1.0 / lambda);
    cov_matrix = vector<vector<double>>(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
    {
        cov_matrix[i][i] = 1.0;
    }
}

vector<double> CMAES::optimize(int max_iterations, function<double(const vector<double> &)> objective_function)
{
    for (int iter = 0; iter < max_iterations; iter++)
    {
        vector<vector<double>> samples = generate_samples();
        vector<pair<double, vector<double>>> evaluated_samples = evaluate_samples(samples, objective_function);
        update_distribution(evaluated_samples);
    }
    return mean;
}

vector<vector<double>> CMAES::generate_samples()
{
    normal_distribution<double> dist(0.0, 1.0);
    vector<vector<double>> samples(lambda, vector<double>(n));
    for (int k = 0; k < lambda; k++)
    {
        for (int i = 0; i < n; i++)
        {
            samples[k][i] = mean[i] + sigma * rng.generate();
        }
    }
    return samples;
}

vector<pair<double, vector<double>>> CMAES::evaluate_samples(
    const vector<vector<double>> &samples, 
    function<double(const vector<double> &)> objective_function
    )
{
    vector<pair<double, vector<double>>> evaluated_samples(lambda);
    for (int k = 0; k < lambda; k++)
    {
        double value = objective_function(samples[k]);
        evaluated_samples[k] = make_pair(value, samples[k]);
    }
    sort(evaluated_samples.begin(), evaluated_samples.end());
    return evaluated_samples;
}

void CMAES::update_distribution(const vector<pair<double, vector<double>>> &evaluated_samples)
{
    vector<double> new_mean(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < lambda; k++)
        {
            new_mean[i] += weights[k] * evaluated_samples[k].second[i];
        }
    }
    mean = new_mean;
}
