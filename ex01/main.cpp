#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"<RPN expression>\"" << std::endl;
        return 1;
    }
    try
    {
        RPN rpn(argv[1]);
        std::cout << rpn.to_string() << std::endl;
        std::cout << rpn.calc() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
