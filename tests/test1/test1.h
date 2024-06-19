#include <vector>
#include <string>

#include "../../generators/random_number_generator.h"

class Test1
{
public:
    static void run();

private:
    static void execute_test(RandomNumberGenerator &generator, int seed, const std::string &filename);
    static int generate_sample(RandomNumberGenerator &generator);
};