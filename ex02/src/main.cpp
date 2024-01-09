#include "PmergeMe.hpp"
#include <set>

bool    checkInput( int argc, char** argv );
bool    isValidInt( std::string const & num );

int main( int argc, char** argv )
{
    if (!checkInput(argc, argv))
    {
        std::cout << "Error.\n";
        return 1;
    }

    PmergeMe    sort(argv);
    return 0;
}

bool    checkInput( int argc, char** argv )
{
    std::set<int>   numbers;
    long            num;

    if (argc < 2)
        return false;
    for (int i = 1; argv[i]; i++)
    {
        if (isValidInt(argv[i]))
        {
            num = atol(argv[i]);
            if (numbers.find(num) == numbers.end())
                numbers.insert(num);
            else
                return false;
        }
        else    
            return false;
    }
    return true;
}

bool    isValidInt( std::string const & num )
{
    size_t  i = 0;
    long    check;

    if (num[i] == '+'|| num[i] == '-')
        i++;
    for (size_t j(i); i < num.length(); j ++, i++)
    {
        if (!isdigit(num[j]))
            return false;
    }
    if (i == 0 || num[i] == '+'|| num[i] == '-')
        return false;
    check = atol(num.c_str());
    if (check < 0 || check > 2147483647)
        return false;
    return true;
}