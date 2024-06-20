#include <vector>
#include <string>

#include "../../generators/random_number_generator.h"

class Test2
{
public:
    static void run();

private:
    static void execute_test(RandomNumberGenerator &generator, double dimension, const std::string &filename);
    static std::vector<double> merge_vectors(const std::vector<std::vector<double>>& data);
    static std::vector<std::pair<double, double>> compute_ECDF(std::vector<double>& data);
    static std::vector<std::pair<double, double>> group_and_compute_ECDF(const std::vector<std::pair<double, double>>& ecdf, int num_bins);
};