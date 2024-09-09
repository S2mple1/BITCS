#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "parser.hpp"

using namespace std;

struct Token{
    yytokentype type;
    string value;
};


#endif