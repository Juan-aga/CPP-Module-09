#include <BitcoinExchange.hpp>

int main( int argc, char **argv )
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " input_file.txt\n";
        return -1;
    }

    BitcoinExchange btc;

    if (!btc.processFile(argv[1]))
        return -1;

    return 0;
}