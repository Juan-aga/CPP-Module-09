#ifndef RPN_H
# define RPN_H

# include <iostream>
# include <stack>
# include <sstream>

class RPN
{
    private:
        std::stack<int> _result;
        bool            _error;

        void            operations( std::string const & token );

    public:
        RPN( void );
        RPN( RPN const & rpn );
        ~RPN( void );

        RPN &   operator=( RPN const & rpn );

        int     process( std::string const & polish );
        bool    fail( void );
};

#endif