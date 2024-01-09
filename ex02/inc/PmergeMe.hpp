#ifndef PMERGEME_H
# define PMERGEME_H

# include <iostream>
# include <vector>
# include <list>
# include <ctime>
# include <cstdlib>
# include <algorithm>

class PmergeMe
{
    private:
        PmergeMe( void );
        PmergeMe( PmergeMe const & pme );
        PmergeMe &  operator=( PmergeMe const & pme );
        void        displayInfo( std::vector<int> nums, std::string const & label );
        template <typename T>
        static void sort(T & cont);

    public:
        PmergeMe( char** const & argv );
        ~PmergeMe( void );

};

#endif