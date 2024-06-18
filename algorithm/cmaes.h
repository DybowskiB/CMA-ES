#pragma once

#include "../newmat11/newmat.h"
#include "../newmat11/newmatio.h"
#include "../newmat11/newmatap.h"
#include "../generators/random_number_generator.h"

#include <vector>
#include <functional>

class CMAES {
public:
    CMAES(int, int, RandomNumberGenerator&);

    void optimize(int, double, std::function<double(const RowVector&)>);

private:
    // population
    int nrows;                                      // number of individuals in the optimization problem
    int ncols;                                      // number of variables in the optimization problem
    Matrix population;

    // decision
    Matrix means;                                   // means of decision variables
    SymmetricMatrix cov;                            // covariance matrix
    ColumnVector pc;                                // path vector
    ColumnVector psigma;                            // path vector

    // parameters of the covariance matrix adaptiation (CMA) evolutionary algorithm (CMA-ES)
    int mu;                                         // mu-best relevant individuals (updating covariance matrix)
    double wi;                                      // could be a single value or a vector comprising the weights of individuals
    double mueff;                                   // 1 <= mueff  <= mu -> the variance effective selection mass
    double mucov;                                   // parameter for weighting between rank-one and rank-mu update
    double ccov;                                    // <= 1, learning rate for cumulation for the rank-one update + covariance matrix
    double cc;                                      // 1/cc is the bacward time horizon
    double csigma;                                  // 1/csigma is the backward time horizon
    double dsigma;                                  // damping parameter for the step size update
    double sigma;                                   // adaptive learning rate

    // eigen-variables
    DiagonalMatrix D;                               // contains the eigenvalues of the covariance matrix
    Matrix V;                                       // contains the eigenvectors column-wise

    // other
    int max_iterations;                             // max iteration in CMA-ES
    double sigma_limit;                             // lower sigma limitation (> sigma_limit)
    RandomNumberGenerator& rng;                     // random number generator


    // initialization methods
    void initialize_population();
    void initialize_covariance_matrix();
    SymmetricMatrix get_empirical_covariance_matrix(const Matrix&);

    // methods calculating variables
    Matrix calculate_new_means();
    Matrix calculate_muupdate();

    // methods updating parameters
    void update_population();
    void update_parameters();
    void update_pc(const Matrix&);
    void update_cov(const Matrix&);
    void update_psigma(const Matrix&);
    void update_sigma();

    // other
    void sort_population(Matrix&, function<double(const RowVector&)>);
    void eigenvalues_decomposition();
    double EN01_approximation(int);
};