#include "./test2.h"
#include "../../algorithm/cmaes.h"
#include "../../generators/random_number_generator.h"
#include "../../generators/mersenne_twister/mersenne_twister_generator.h"
#include "../../generators/linear_congruential/linear_congruential_generator.h"
#include "../../generators/xoroshiro/xoroshiro_generator.h"
#include "../../generators/halton/halton_generator.h"
#include "../../generators/lagged_fibonacci/lagged_fibonacci_generator.h"
#include "../../generators/chacha20/chacha20.h"
#include "../../CEC17_fast_pow/cec17_test_fast_pow.h"

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <filesystem>

void Test2::run()
{
    const int seed = 12345;

    std::vector<RandomNumberGenerator *> generators{
        new ChaCha20Generator(seed),
        new HaltonGenerator(1, seed),
        new LaggedFibonacciGenerator(seed),
        new LinearCongruentialGenerator(seed),
        new XoroshiroGenerator(seed),
        new MersenneTwisterGenerator(seed)
    };

    const int num_of_dimensions = 2;
    double dimensions[num_of_dimensions] = {10, 50};

    int max_test_number = generators.size() * num_of_dimensions;
    for (size_t i = 0; i < generators.size(); ++i)
    {
        for (int j = 0; j < num_of_dimensions; ++j)
        {
            std::cout << "Executing test number " << i * num_of_dimensions + j + 1 << "/" << max_test_number << "..." << std::endl;
            std::string filename = "./tests/output/cmaes_" + generators[i]->to_string() + "_" + std::to_string(dimensions[j]);
            execute_test(*generators[i], dimensions[j], filename);
            std::cout << "Executed test number " << i * num_of_dimensions + j + 1 << "/" << max_test_number << "." << std::endl;
        }
    }

    // Free resources
    for (auto *generator : generators)
    {
        delete generator;
    }
}

void Test2::execute_test(RandomNumberGenerator &generator, double dimension, const std::string &filename)
{
    const int population_size = 100;
    const int max_iteration = 1000;
    const double min_sigma = 0.001;
    const int num_bins = 10;

    CMAES cmaes1(population_size, dimension, generator);
    CMAES cmaes2(population_size, dimension, generator);
    CMAES cmaes3(population_size, dimension, generator);
    
    // optimze for each function
    std::vector<vector<double>> results_sphere = cmaes1.optimize(max_iteration, min_sigma, sphere_func);
    std::vector<vector<double>> results_ackley = cmaes2.optimize(max_iteration, min_sigma, ackley_func);
    std::vector<vector<double>> results_rastrigin = cmaes3.optimize(max_iteration, min_sigma, rastrigin_func);

    // Prepare sphere function data
    std::vector<double> merged_results_sphere = merge_vectors(results_sphere);
    std::vector<std::pair<double, double>> ecdf_sphere = compute_ECDF(merged_results_sphere);
    std::vector<std::pair<double, double>> grouped_ecdf_sphere = group_and_compute_ECDF(ecdf_sphere, num_bins);

    // Prepare ackley function data
    std::vector<double> merged_results_ackley = merge_vectors(results_ackley);
    std::vector<std::pair<double, double>> ecdf_ackley = compute_ECDF(merged_results_ackley);
    std::vector<std::pair<double, double>> grouped_ecdf_ackley = group_and_compute_ECDF(ecdf_ackley, num_bins);

    // Prepare rastrigin function data
    std::vector<double> merged_results_rastrigin = merge_vectors(results_rastrigin);
    std::vector<std::pair<double, double>> ecdf_rastrigin = compute_ECDF(merged_results_rastrigin);
    std::vector<std::pair<double, double>> grouped_ecdf_rastrigin = group_and_compute_ECDF(ecdf_rastrigin, num_bins);

    // Save result to file (overwrites if file exists)
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    file << "Generator: " << generator.name << std::endl;
    file << "Dimension: " << dimension << std::endl;
    file << std::endl << std::endl;

    file << "1. Sphere function:" << std::endl;
    file << "Number of iterations: " << results_sphere.size() << std::endl;
    file << "Final sigma value: " << cmaes1.get_sigma() << std::endl;
    for (const auto& [x, y] : grouped_ecdf_sphere)
    {
        file << "x: " << x << ", ECDF: " << y << std::endl;
    }
    file << std::endl;

    file << "2. Ackley function:" << std::endl;
    file << "Number of iterations: " << results_ackley.size() << std::endl;
    file << "Final sigma value: " << cmaes2.get_sigma() << std::endl;
    for (const auto& [x, y] : grouped_ecdf_ackley)
    {
        file << "x: " << x << ", ECDF: " << y << std::endl;
    }
    file << std::endl;

    file << "3. Rastrigin function:" << std::endl;
    file << "Number of iterations: " << results_rastrigin.size() << std::endl;
    file << "Final sigma value: " << cmaes3.get_sigma() << std::endl;
    for (const auto& [x, y] : grouped_ecdf_rastrigin)
    {
        file << "x: " << x << ", ECDF: " << y << std::endl;
    }

    // Close file
    file.close();
}

std::vector<double> Test2::merge_vectors(const std::vector<std::vector<double>>& data)
{
    std::vector<double> merged;
    for (const auto& vec : data)
    {
        merged.insert(merged.end(), vec.begin(), vec.end());
    }
    return merged;
}

std::vector<std::pair<double, double>> Test2::compute_ECDF(std::vector<double>& data)
{
    std::vector<std::pair<double, double>> ecdf;
    std::sort(data.begin(), data.end());

    for (size_t i = 0; i < data.size(); ++i)
    {
        double x = data[i];
        double y = static_cast<double>(i + 1) / data.size();
        ecdf.emplace_back(x, y);
    }
    return ecdf;
}

std::vector<std::pair<double, double>> Test2::group_and_compute_ECDF(const std::vector<std::pair<double, double>>& ecdf, int num_bins)
{
    std::vector<std::pair<double, double>> grouped_ecdf;
    int bin_size = ecdf.size() / num_bins;

    for (int i = 0; i < num_bins; ++i)
    {
        double sum_x = 0;
        double sum_y = 0;
        for (int j = 0; j < bin_size; ++j) {
            int index = i * bin_size + j;
            if (static_cast<long unsigned int>(index) < ecdf.size())
            {
                sum_x += ecdf[index].first;
                sum_y += ecdf[index].second;
            }
        }
        double avg_x = sum_x / bin_size;
        double avg_y = sum_y / bin_size;
        grouped_ecdf.emplace_back(avg_x, avg_y);
    }
    return grouped_ecdf;
}
