#include "PmergeMe.hpp"

PmergeMe::PmergeMe( char** const & argv )
{
    std::vector<int>    dataV;
    std::list<int>      dataL;
    std::clock_t        start;
    double              duration;

    for (int i = 1; argv[i]; i++)
    {
        dataV.push_back(atoi(argv[i]));
        dataL.push_back(atoi(argv[i]));
    }

    displayInfo(dataV, "Before");
    start = std::clock();
    sort(dataV);
    duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
    displayInfo(dataV, "After");
    std::cout << "Time to process a range of " << dataV.size();
    std::cout << " elements with std::vector : " << std::fixed << duration << " us\n";

    start = std::clock();
    sort(dataL);
    duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << dataL.size();
    std::cout << " elements with std::list : " << std::fixed << duration << " us\n";
}

PmergeMe::~PmergeMe( void )
{

}

void        PmergeMe::displayInfo( std::vector<int> nums, std::string const & label )
{
    std::cout << label << ":\t";
    for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

template <typename T>
void        PmergeMe::sort( T & cont )
{
    if (cont.size() < 2)
        return;
    
    typename T::iterator    middle = cont.begin();
    std::advance(middle, cont.size() / 2);

    T   left(cont.begin(), middle);
    T   right(middle, cont.end());
    
    sort(left);
    sort(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(), cont.begin());
}