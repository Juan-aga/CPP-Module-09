#include <RPN.hpp>

int main( int argc, char **argv )
{
    int result;

    if (argc != 2)
    {
        std::cerr << "Error\n";
        return 1;
    }
    
    RPN calculator;
    result = calculator.process(argv[1]);
    if (calculator.fail())
    {
        std::cerr << "Error\n";
        return 1;
    }
    std::cout << result << std::endl;
    return 0;

}