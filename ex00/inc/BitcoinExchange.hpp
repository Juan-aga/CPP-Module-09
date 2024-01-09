#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <map>
# include <ctime>
# include <iostream>
# include <fstream>
# include <sstream>
# include <stdlib.h>
# include <cmath>


# define DATABASE "data.csv"

class  BitcoinExchange
{
    private:
        std::map<std::time_t, float>    _data;

        bool        loadDb( void );
        std::time_t stringToDate( std::string const & String );
        bool        checkData( std::string const & line);
        float       findValue( std::time_t date );

    public:
        BitcoinExchange( void );
        BitcoinExchange( BitcoinExchange const & btc );
        ~BitcoinExchange( void );

        BitcoinExchange &   operator=( BitcoinExchange const & btc );

        bool                processFile( std::string const & fileName );
};

#endif