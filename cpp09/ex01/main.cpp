#include "RPN.hpp"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    RPN calculator;
    long long result = 0;
    std::string error;
    if (!calculator.evaluate(argv[1], result, error))
    {
        std::cerr << "Error: " << error << std::endl;
        return 1;
    }
    std::cout << result << std::endl;
    return 0;
}
