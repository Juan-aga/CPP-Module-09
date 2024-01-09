#include <BitcoinExchange.hpp>

BitcoinExchange::BitcoinExchange( void )
{
    if (!loadDb())
    {
        std::cerr << "Failed to open database file " << DATABASE << ".\n";
        exit(-1);
    }
}

BitcoinExchange::BitcoinExchange( BitcoinExchange const & btc ):_data(btc._data)
{

}

BitcoinExchange::~BitcoinExchange( void )
{

}

BitcoinExchange &   BitcoinExchange::operator=( BitcoinExchange const & btc )
{
    if (this != &btc)
        _data = btc._data;
    return *this;
}

bool                BitcoinExchange::loadDb( void )
{
    std::ifstream   db(DATABASE);
    std::string     line;

    if (!db.is_open())
        return false;
    std::getline(db, line);
    while(std::getline(db, line))
    {
        std::istringstream  ss(line);
        std::string         dateStr, value;
        std::time_t         date;

        std::getline(ss, dateStr, ',');
        std::getline(ss, value, ',');
        date = stringToDate(dateStr);
        _data[date] = std::atof(value.c_str());
    }
    // if (DEBUG)
    // {
    //     std::cout << "DATABASE:\n";
    //     std::map<std::time_t, float>::const_iterator it;
    //     for (it = _data.begin(); it != _data.end(); it++)
    //     {
    //         std::time_t timestamp = it->first;
    //         float value = it->second;

    //         char  datePrint[11];

	//         std::strftime(datePrint, 11, "%Y-%m-%d", localtime(&timestamp));
    //         std:: cout << "DATE: " << std::string(datePrint) << "\tVALUE: " << value << std::endl;
    //     }
    // }
    return true;
}

std::time_t         BitcoinExchange::stringToDate( std::string const & String )
{
    struct tm      tm = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int                 year, month, day, check;

    check = sscanf(String.c_str(), "%d-%d-%d", &year, &month, &day);
    if (check == 3 && (month > 0 && month <= 12 && day > 0 && day <= 31))
    {
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
    }
    else
        return -1;
    return std::mktime(&tm);
}

bool                BitcoinExchange::processFile( std::string const & fileName )
{
    std::ifstream   file(fileName.c_str());
    std::string     line;

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file.\n";
        return false;
    }
    std::getline(file, line);
    while(std::getline(file, line))
    {
        checkData(line);
    }
    return true;
}

bool                BitcoinExchange::checkData( std::string const & line)
{
    std::istringstream  ss(line);
    std::string         dateStr, value;
    std::time_t         date;
    float               num;

    std::getline(ss, dateStr, '|');
    std::getline(ss, value, '|');
    date = stringToDate(dateStr);
    num = std::atof(value.c_str());

    if (line.find("|") == std::string::npos)
        std::cerr << "Error: bad input => " << line << std::endl;
    else if (date == -1)
        std::cerr << "Error: bad date: " << dateStr << std::endl;
    else if (num < 0)
        std::cerr << "Error: not a positive number.\n";
    else if (num > 1000)
        std::cerr << "Error: too large a number.\n";
    else
    {
        std::cout << dateStr << " => " << num << " = " << num * findValue(date) << std::endl;
    }
    return false;
}

float               BitcoinExchange::findValue( std::time_t date)
{
    std::map<std::time_t, float>::iterator  it;

    it = _data.begin();
    for (; it != _data.end() && it->first <= date; it++);
    if (it != _data.begin())
        it--;
    if (DEBUG)
    {
        char  datePrint[11];

        std::strftime(datePrint, 11, "%Y-%m-%d", localtime(&it->first));
        std::cerr << "\nFOUND " << datePrint << "\tvalue: " << it->second << std::endl;
    }
    return it->second;
}