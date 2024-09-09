%{
#include <stdio.h>
#include <vector>
#include<string>
#include "tokens.hpp"
using namespace std;

extern vector<Token> tokens;
int tokenCount = 0;
%}

%%

"int"       { tokens.push_back({INT, yytext}); yylval.index = tokenCount++; return INT; }
"return"    { tokens.push_back({RETURN, yytext}); yylval.index = tokenCount++; return RETURN; }
"main"      { tokens.push_back({MAIN, yytext}); yylval.index = tokenCount++; return MAIN; }
"void"      { tokens.push_back({VOID, yytext}); yylval.index = tokenCount++; return VOID; }
"println_int" { tokens.push_back({PREDEFINED_FUNCTION, yytext}); yylval.index = tokenCount++; return PREDEFINED_FUNCTION; }
[0-9]+      { tokens.push_back({NUMBER, yytext}); yylval.index = tokenCount++; return NUMBER; }
[a-zA-Z_][a-zA-Z_0-9]* { tokens.push_back({IDENTIFIER, yytext}); yylval.index = tokenCount++; return IDENTIFIER; }
"="         { tokens.push_back({ASSIGN, yytext}); yylval.index = tokenCount++; return ASSIGN; }
"+"         { tokens.push_back({ADD, yytext}); yylval.index = tokenCount++; return ADD; }
"-"         { tokens.push_back({SUB, yytext}); yylval.index = tokenCount++; return SUB; }
"!"         { tokens.push_back({NOT, yytext}); yylval.index = tokenCount++; return NOT; }
"~"         { tokens.push_back({BITWISE_NOT, yytext}); yylval.index = tokenCount++; return BITWISE_NOT; }
"*"         { tokens.push_back({MUL, yytext}); yylval.index = tokenCount++; return MUL; }
"/"         { tokens.push_back({DIV, yytext}); yylval.index = tokenCount++; return DIV; }
"%"         { tokens.push_back({MOD, yytext}); yylval.index = tokenCount++; return MOD; }
"<"         { tokens.push_back({LESS, yytext}); yylval.index = tokenCount++; return LESS; }
"<="        { tokens.push_back({LESS_EQUAL, yytext}); yylval.index = tokenCount++; return LESS_EQUAL; }
">"         { tokens.push_back({GREATER, yytext}); yylval.index = tokenCount++; return GREATER; }
">="        { tokens.push_back({GREATER_EQUAL, yytext}); yylval.index = tokenCount++; return GREATER_EQUAL; }
"=="        { tokens.push_back({EQUAL, yytext}); yylval.index = tokenCount++; return EQUAL; }
"!="        { tokens.push_back({NOTEQUAL, yytext}); yylval.index = tokenCount++; return NOTEQUAL; }
"&"         { tokens.push_back({BITWISE_AND, yytext}); yylval.index = tokenCount++; return BITWISE_AND; }
"|"         { tokens.push_back({BITWISE_OR, yytext}); yylval.index = tokenCount++; return BITWISE_OR; }
"^"         { tokens.push_back({BITWISE_XOR, yytext}); yylval.index = tokenCount++; return BITWISE_XOR; }
"&&"        { tokens.push_back({LOGICAL_AND, yytext}); yylval.index = tokenCount++; return LOGICAL_AND; }
"||"        { tokens.push_back({LOGICAL_OR, yytext}); yylval.index = tokenCount++; return LOGICAL_OR; }
";"         { tokens.push_back({SEMICOLON, yytext}); yylval.index = tokenCount++; return SEMICOLON; }
"{"         { tokens.push_back({LEFT_BRACE, yytext}); yylval.index = tokenCount++; return LEFT_BRACE; }
","         { tokens.push_back({COMMA, yytext}); yylval.index = tokenCount++; return COMMA; }
"}"         { tokens.push_back({RIGHT_BRACE, yytext}); yylval.index = tokenCount++; return RIGHT_BRACE; }
"("         { tokens.push_back({LEFT_PAREN, yytext}); yylval.index = tokenCount++; return LEFT_PAREN; }
")"         { tokens.push_back({RIGHT_PAREN, yytext}); yylval.index = tokenCount++; return RIGHT_PAREN; }
[ \t\n]     { /* ignore whitespace */ }
.           { tokens.push_back({UNKNOWN, yytext}); yylval.index = tokenCount++; return UNKNOWN; }

%%
int yywrap() {
    return 1;
}