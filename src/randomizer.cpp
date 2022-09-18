#include "randomizer.h"

int GenerateNumber(const int from, const int to)
{
    // Create a random device and use it to generate a random seed
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();

    // Initialize a default_random_engine with the seed
    std::default_random_engine myRandomEngine(seed);

    // Initialize a uniform_int_distribution to produce values between -10 and 10
    std::uniform_int_distribution<int> myUnifIntDist(from, to);

    // Create and print 5 randomly generated values
    for (int i = 0; i < 5; i++)
    {
        int number = myUnifIntDist(myRandomEngine);
        std::cout << number << std::endl;
    }
    return myUnifIntDist(myRandomEngine);
};
