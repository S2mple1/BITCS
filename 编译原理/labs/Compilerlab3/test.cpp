//
// Created by zhj on 2024/5/21.
//
#include <string>
#include "tokens.hpp"
using namespace std;


union YYE {
    int ival;
    string sval;
    Token token;
};