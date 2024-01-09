#include <RPN.hpp>

RPN::RPN( void )
{

}

RPN::RPN( RPN const & rpn ): _result(rpn._result)
{

}

RPN::~RPN( void )
{

}

RPN &   RPN::operator=( RPN const & rpn )
{
    if (this != &rpn)
        _result = rpn._result;
    return *this;
}

int     RPN::process( std::string const & polish )
{
    std::istringstream  ss(polish);
    std::string         token;


    _error = false;
    while (ss >> token)
    {
        if (DEBUG)
            std::cout << "TOKEN: " << token << std::endl;
        if (token.size() != 1)
            _error = true;
        else if (isdigit(token[0]))
            _result.push(token[0] - '0');
        else
            operations(token);
        if (_error)
            return 0;
    }
    if (_result.size() != 1)
        _error = true;
    return _result.top();
}

bool    RPN::fail( void )
{
    return _error;
}

void    RPN::operations( std::string const & token )
{
    int                 num1;
    int                 num2;

    num2 = _result.top();
    _result.pop();
    num1 = _result.top();
    _result.pop();
    if (token == "+")
        _result.push(num1 + num2);
    else if (token == "-")
        _result.push(num1 - num2);
    else if (token == "*")
        _result.push(num1 * num2);
    else if (token == "/")
    {
        if (!num2)
            _error = true;
        else
            _result.push(num1 / num2);
    }
    else
        _error = true;
    if (DEBUG)
        std::cout << "RESULT: " << _result.top() << std::endl;
}