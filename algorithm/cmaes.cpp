#include "cmaes.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <functional>

using namespace std;

CMAES::CMAES(int nrows, int ncols, RandomNumberGenerator& rng_generator)
    : nrows(nrows), ncols(ncols), population(nrows, ncols), means(ncols, 1), cov(ncols), pc(ncols), psigma(ncols), rng(rng_generator)
{
    // decision
    means = 0.0;
    pc = 0.0;
    psigma = 0.0;
    
    // parameters of the CMA-ES
    mu = nrows / ncols;
    wi = 1.0 / mu;
    mueff = std::pow(mu * wi, 2) / (mu * pow(wi, 2));
    mucov = mueff;
    ccov = (1/ mucov) * 2 / std::pow(ncols + 1.4, 2) + (1 - 1 / mucov) * ((2 * mueff - 1) / (std::pow(ncols + 2, 2) + 2 * mueff));
    cc = 1.0 / ncols;
    csigma = cc;
    dsigma = 1;
    sigma = 1.0;

    initialize_population();
    initialize_covariance_matrix();
}

void CMAES::optimize(int max_iterations, double sigma_limit, function<double(const RowVector&)> objective_function)
{
    for (int k = 0; k < max_iterations && sigma > sigma_limit; ++k)
    {
        /*std:cout << "Iteration: " << k << " - sigma=" << sigma << ":\n" << population << "\n\n\nFitness:\n";
        for (int i = 0; i < nrows; ++i)
            std::cout << objective_function(population.row(i + 1)) << std::endl;*/

        eigenvalues_decomposition();
        update_population();
        sort_population(population, objective_function);
        update_parameters();
    }
}

void CMAES::initialize_population()
{
    for (int i = 0; i < nrows; ++i)
    {
        for (int j = 0; j < ncols; ++j)
        {
            population.element(i, j) = rng.generate(-5, 5);
        }
    }
    means = (population.sum_columns() / double(nrows)).t();
}

void CMAES::initialize_covariance_matrix()
{
    cov = get_empirical_covariance_matrix(population);
}

SymmetricMatrix CMAES::get_empirical_covariance_matrix(const Matrix& m)
{
    SymmetricMatrix cov(m.ncols());
    cov = 0.0;
    ColumnVector colSums = m.sum_columns().t();

    for (int i = 0; i < m.nrows(); ++i)
    {
        for (int j = 0; j < m.ncols(); ++j)
        {
            Matrix multiplication_component = m.row(i + 1).t() - 1.0 / m.nrows() * colSums;
            SymmetricMatrix aux_matrix;
            aux_matrix << multiplication_component * multiplication_component.t();
            cov += aux_matrix;
        }
    }

    return 1.0 / (m.nrows() - 1) * cov;
}

void CMAES::sort_population(Matrix& m, function<double(const RowVector&)> objective_function)
{
    bool terminated;
    do {
        terminated = true;
        for (int i = 0; i < m.nrows(); ++i)
        {
            if (objective_function(m.row(i + 1)) > objective_function(m.row(i)))
            {
                RowVector temp_row;
                temp_row << m.row(i);
                m.row(i) << m.row(i + 1);
                m.row(i + 1) << temp_row;
                terminated = false;
            }
        }
    } while (!terminated);
}

void CMAES::eigenvalues_decomposition()
{
    // eigenvalues decomposition cov = V * D^2 * V^T
    eigenvalues(cov, D, V);
    for (int l = 0; l < D.nrows(); ++l)
    {
        D.element(l, l) = sqrt(D.element(l, l));
    }
}

void CMAES::update_population()
{
    for (int i = 0; i < nrows; ++i)
    {
        ColumnVector randVec(ncols);
        for (int j = 0; j < ncols; ++j)
        {
            randVec.element(j) = rng.generate(0, 1);
        }
        Matrix auxiliary_matrix = means + sigma * V * D * randVec;
        population.row(i + 1) = auxiliary_matrix.t();
    }
}

double CMAES::EN01_approximation(int n)
{
    return sqrt(n) * (1 - 1.0 / (4 * n) + 1.0 / (21 * n * n));
}

void CMAES::update_parameters()
{
    Matrix new_means = calculate_new_means();
    update_pc(new_means);
    Matrix muupdate = calculate_muupdate();
    update_cov(muupdate);
    update_psigma(new_means);
    update_sigma();
    means << new_means;
}

Matrix CMAES::calculate_new_means()
{
    Matrix new_means(ncols, 1);
    new_means = 0.0;
    for (int i = 0; i < mu; ++i)
    {
        new_means += (wi * population.row(i + 1)).t();
    }
    return new_means;
}

void CMAES::update_pc(const Matrix& new_means)
{
    pc = (1 - cc) * pc + sqrt(cc * (2 - cc) * mueff) * (new_means - means) / sigma;
}

Matrix CMAES::calculate_muupdate()
{
    Matrix muupdate(ncols, ncols);
    muupdate = 0.0;
    for (int i = 0; i < mu; ++i)
    {
        Matrix rhs = (population.row(i + 1).t() - means) / sigma;
        muupdate += wi * rhs * rhs.t();
    }
    return muupdate;
}

void CMAES::update_cov(const Matrix& muupdate)
{
    cov << (1 - ccov) * cov + ccov / mucov * pc * pc.t() + ccov * (1 - 1 / mucov) * muupdate;
}

void CMAES::update_psigma(const Matrix& new_means)
{
    SymmetricMatrix cov12;
    cov12 << V * D.i() * V.t();
    psigma = (1 - csigma) * psigma + sqrt(csigma * (2 - csigma) * mueff) * cov12 * (new_means - means) / sigma;
}

void CMAES::update_sigma()
{
    sigma = sigma * exp(csigma / dsigma * (sqrt(psigma.sum_square()) / EN01_approximation(ncols) - 1));
}
