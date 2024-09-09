%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "tokens.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

void yyerror(const char *s);
int yylex();
void clearStack();
void opreate(yytokentype opType);
string tokenTypeToString(int type);
void clearStackInFunc(int num);
extern void yy_scan_string(const char *str);
extern vector<Token> tokens;

vector<string> functions;
vector<int> functionVars;
vector<int> callArgs;
int functionIndex = 0;
int call_args = 0;
int localVariableCount = 0;
int inputVariableCount = 0;
int zerocnt = 0;
int onecnt = 0;
int notcnt = 0;
int opCountOutSideCall = 0;
bool singleExpression = true;
bool isNumCall = false;

unordered_map<string, int> inputVariables;
unordered_map<string, int> localVariables;

stack <int> operators;
stack <int> oprands;

unordered_map <yytokentype, int> priority = {
    {MUL, 1},
    {DIV, 1},
    {MOD, 1},
    {ADD, 2},
    {SUB, 2},
    {LESS, 3},
    {LESS_EQUAL, 3},
    {GREATER, 3},
    {GREATER_EQUAL, 3},
    {EQUAL, 4},
    {NOTEQUAL, 4},
    {BITWISE_AND, 5},
    {BITWISE_XOR, 6},
    {BITWISE_OR, 7},
    {LOGICAL_AND, 8},
    {LOGICAL_OR, 9},
    {ASSIGN, 10},
    {LEFT_PAREN, 11},
    {RIGHT_PAREN, 11},
};

%}

%error-verbose

%union {
    int index;
}

%token <index> NUMBER
%token <index> IDENTIFIER
%token <index> INT RETURN MAIN VOID PREDEFINED_FUNCTION
%token <index> ASSIGN ADD SUB MUL DIV MOD
%token <index> LESS LESS_EQUAL GREATER GREATER_EQUAL
%token <index> EQUAL NOTEQUAL
%token <index> BITWISE_AND BITWISE_OR BITWISE_XOR
%token <index> LOGICAL_AND LOGICAL_OR
%token <index> NOT BITWISE_NOT
%token <index> SEMICOLON LEFT_BRACE RIGHT_BRACE LEFT_PAREN RIGHT_PAREN
%token <index> COMMA
%token <index> UNKNOWN

%type <index> expression statement

%right ASSIGN
%left LOGICAL_OR
%left LOGICAL_AND
%left BITWISE_OR
%left BITWISE_XOR
%left BITWISE_AND
%left EQUAL NOTEQUAL
%left LESS GREATER LESS_EQUAL GREATER_EQUAL
%left ADD SUB
%left MUL DIV MOD
%right NOT BITWISE_NOT
%left LEFT_PAREN RIGHT_PAREN

%%

program:
    function_list
    ;

function_list:
    function
    | function function_list
    ;

function:
    main_function {
        printf("pop eax\n");
        printf("leave\n");
        printf("ret\n");
    }
    | other_function {
        printf("leave\n");
        printf("ret\n");
    }
    ;

args:
    /* empty */
    | INT IDENTIFIER{
        inputVariables[tokens[$2].value] = ++inputVariableCount;
    }
    | args COMMA INT IDENTIFIER {
        inputVariables[tokens[$4].value] = ++inputVariableCount;
    }
    ;

main_function:
    INT MAIN LEFT_PAREN args RIGHT_PAREN{
            inputVariableCount = 0;
        }
        LEFT_BRACE {
            cout << endl << "main:" << endl;
            cout << "push ebp" << endl;
            cout << "mov ebp, esp" << endl;
            cout << "sub esp, " << 4 * functionVars[functionIndex++] << endl;
            localVariableCount = 0;
        }
    statement_list RIGHT_BRACE{
        inputVariables.clear();
        localVariables.clear();
    }
    ;

other_function:
    INT IDENTIFIER LEFT_PAREN args RIGHT_PAREN{
            for(auto it = inputVariables.begin(); it != inputVariables.end(); it++){
                inputVariables[it->first] = inputVariableCount + 1 - inputVariables[it->first];
            }
            inputVariableCount = 0;
        }
        LEFT_BRACE {
            cout << endl << tokens[$2].value << ":" << endl;
            printf("push ebp\n");
            printf("mov ebp, esp\n");
            printf("sub esp, %d\n", 4 * functionVars[functionIndex++] + 4);
            localVariableCount = 0;
    }
    statement_list RIGHT_BRACE{
        inputVariables.clear();
        localVariables.clear();
    }
    | VOID IDENTIFIER LEFT_PAREN args RIGHT_PAREN{
            for(auto it = inputVariables.begin(); it != inputVariables.end(); it++){
                inputVariables[it->first] = inputVariableCount + 1 - inputVariables[it->first];
            }
            inputVariableCount = 0;
        }
        LEFT_BRACE {
            cout << endl << tokens[$2].value << ":" << endl;
            printf("push ebp\n");
            printf("mov ebp, esp\n");
            printf("sub esp, %d\n", 4 * functionVars[functionIndex++] + 4);
            localVariableCount = 0;
    }
    statement_list RIGHT_BRACE{
        inputVariables.clear();
        localVariables.clear();
    }
    ;

statement_list:
    statement{
        singleExpression = true;
    }
    | statement{
        singleExpression = true;
    } statement_list
    ;

statement:
    /* empty */
    | INT declaration_list SEMICOLON{
    }
    | IDENTIFIER ASSIGN expression SEMICOLON{
        int offset;
        clearStack();
        if(inputVariables.find(tokens[$1].value) != inputVariables.end()){
            offset = 4 * (inputVariables[tokens[$1].value] + 1);
            printf("pop eax\n");
            printf("mov DWORD PTR [ebp + %d], eax\n", offset);
        } else if(localVariables.find(tokens[$1].value) != localVariables.end()){
            offset = 4 * localVariables[tokens[$1].value];
            printf("pop eax\n");
            printf("mov DWORD PTR [ebp - %d], eax\n", offset);
        }
    }
    | RETURN expression SEMICOLON{
        clearStack();
        printf("pop eax\n");
    }
    | PREDEFINED_FUNCTION LEFT_PAREN expression RIGHT_PAREN SEMICOLON {
        clearStack();
        printf("push offset format_str\n");
        printf("call printf\n");
        printf("add esp, 8\n");
    }
    | IDENTIFIER{isNumCall = true;} LEFT_PAREN arg_list RIGHT_PAREN SEMICOLON{
        printf("call %s\n", tokens[$1].value.c_str());
        printf("add esp, %d\n", 4 * (call_args + 1));
        printf("push eax\n");
        call_args = 0;
        isNumCall = false;
        opCountOutSideCall = 0;
    }
    ;

declaration_list:
    IDENTIFIER {
        localVariables[tokens[$1].value] = ++localVariableCount;
    }
    | IDENTIFIER ASSIGN expression{
        localVariables[tokens[$1].value] = ++localVariableCount;
        clearStack();
        singleExpression = true;
        printf("pop eax\n");
        printf("mov DWORD PTR [ebp - %d], eax\n", 4 * localVariableCount);
        }
    | declaration_list COMMA IDENTIFIER{
        localVariables[tokens[$3].value] = ++localVariableCount;
        }
    | declaration_list COMMA IDENTIFIER ASSIGN expression{
        localVariables[tokens[$3].value] = ++localVariableCount;
        clearStack();
        singleExpression = true;
        printf("pop eax\n");
        printf("mov DWORD PTR [ebp - %d], eax\n", 4 * localVariableCount);
        }
    ;

arg_list:
    /* empty */
    | expression{
        clearStackInFunc(opCountOutSideCall);
    }
    | arg_list COMMA{call_args++; isNumCall = false;} expression {
        clearStackInFunc(opCountOutSideCall);
    }
    ;

expression:
    NUMBER{
        $$ = $1;
        cout << "push " << tokens[$1].value << endl;
        oprands.push($1);
    }
    | IDENTIFIER{
        $$ = $1;
        int offset;
        if(inputVariables.find(tokens[$1].value) != inputVariables.end()){
            offset = 4 * (inputVariables[tokens[$1].value] + 1);
            printf("mov eax, DWORD PTR [ebp + %d]\n", offset);
            printf("push eax\n");
        } else if(localVariables.find(tokens[$1].value) != localVariables.end()){
            offset = 4 * localVariables[tokens[$1].value];
            printf("mov eax, DWORD PTR [ebp - %d]\n", offset);
            printf("push eax\n");
        }
        oprands.push($1);
    }
    | IDENTIFIER{isNumCall = true; opCountOutSideCall = operators.size();} LEFT_PAREN arg_list RIGHT_PAREN {
            printf("call %s\n", tokens[$1].value.c_str());
            printf("add esp, %d\n", 4 * (call_args + 1));
            printf("push eax\n");
            call_args = 0;
        }
    | expression ADD{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[ADD]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression SUB{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[SUB]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression MUL{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[MUL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression DIV{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[DIV]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression MOD{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[MOD]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);

    } expression
    | expression LESS{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LESS]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression LESS_EQUAL{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LESS_EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression GREATER{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[GREATER]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression GREATER_EQUAL{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[GREATER_EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression EQUAL{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression NOTEQUAL{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[NOTEQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression BITWISE_AND{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_AND]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression BITWISE_OR{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_OR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression BITWISE_XOR{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_XOR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression LOGICAL_AND{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LOGICAL_AND]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);
    } expression
    | expression LOGICAL_OR{
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LOGICAL_OR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push($2);

    } expression
    | NOT expression{
        singleExpression = false;

        printf("pop eax\n");
        printf("cmp eax, 0\n");
        cout << "jnz notZero" << notcnt << endl;
        printf("setz al\n");
        cout << "jmp notEnd" << notcnt << endl;
        cout << "notZero" << notcnt << ":" << endl;
        cout << "mov eax, 0" << endl;
        cout << "notEnd" << notcnt << ":" << endl;
        printf("push eax\n");
        notcnt++;
    }
    | SUB expression %prec BITWISE_NOT{
        singleExpression = false;

        printf("pop eax\n");
        printf("neg eax\n");
        printf("push eax\n");
    }
    | BITWISE_NOT expression{
        singleExpression = false;

        printf("pop eax\n");
        printf("not eax\n");
        printf("push eax\n");
    }
    | LEFT_PAREN{
        operators.push($1);
    } expression RIGHT_PAREN{
        while(tokens[operators.top()].type != LEFT_PAREN){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.pop();
    }
    ;

%%

void init() {
    cout << ".intel_syntax noprefix" << endl;
    cout << ".extern printf" << endl;
    for(auto &function : functions) {
        cout << ".global " << function << endl;
    }
    cout << ".data\nformat_str:\n.asciz \"%d\\n\"\n.text\n" << endl;
}

string tokenTypeToString(int type) {
    switch (type) {
        case NUMBER: return "NUMBER";
        case IDENTIFIER: return "IDENTIFIER";
        case INT: return "INT";
        case RETURN: return "RETURN";
        case MAIN: return "MAIN";
        case VOID: return "VOID";
        case PREDEFINED_FUNCTION: return "PREDEFINED_FUNCTION";
        case ASSIGN: return "ASSIGN";
        case ADD: return "ADD";
        case SUB: return "SUB";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case EQUAL: return "EQUAL";
        case NOTEQUAL: return "NOTEQUAL";
        case BITWISE_AND: return "BITWISE_AND";
        case BITWISE_OR: return "BITWISE_OR";
        case BITWISE_XOR: return "BITWISE_XOR";
        case LOGICAL_AND: return "LOGICAL_AND";
        case LOGICAL_OR: return "LOGICAL_OR";
        case NOT: return "NOT";
        case BITWISE_NOT: return "BITWISE_NOT";
        case SEMICOLON: return "SEMICOLON";
        case LEFT_BRACE: return "LEFT_BRACE";
        case RIGHT_BRACE: return "RIGHT_BRACE";
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case COMMA: return "COMMA";
        case UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}

void print() {
    for (auto &token : tokens) {
        cout << tokenTypeToString(token.type) << "\t" << token.value << endl;
    }
}

void getFunctions(){
    bool inFunction = false;
    int vars = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token& token = tokens[i];
        if(token.type == LEFT_BRACE){
            inFunction = true;
        }
        if(token.type == RIGHT_BRACE){
            inFunction = false;
            functionVars.push_back(vars);
            vars = 0;
        }
        if(token.type == INT && inFunction){
            int comma = 0;
            for (size_t j = i; j < tokens.size(); ++j) {
                if(tokens[j].type == COMMA){
                    comma++;
                }
                if(tokens[j].type == SEMICOLON){
                    vars += comma + 1;
                    break;
                }
            }
        }
        if((token.type == IDENTIFIER || token.type == MAIN) && tokens[i + 1].type == LEFT_PAREN && (tokens[i - 1].type == INT || tokens[i - 1].type == VOID)){
            functions.push_back(token.value);
        }
    }
}

void zero(){
    cout << "zero:" << endl;
    cout << "push 0" << endl;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

void lexing() {
    while(yylex() != 0) {

    }
}

void clearStack(){
    while(!operators.empty()){
        yytokentype op = tokens[operators.top()].type;
        operators.pop();
        opreate(op);
    }
}

void clearStackInFunc(int num){
    while(operators.size() > num){
        yytokentype op = tokens[operators.top()].type;
        operators.pop();
        opreate(op);
    }
}

void opreate(yytokentype opType){ 
    switch(opType){
        case ADD:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "add eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case SUB:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "sub eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case MUL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "imul eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case DIV:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cdq" << endl;
            cout << "idiv ebx" << endl;
            cout << "push eax" << endl;
            break;
        case MOD:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cdq" << endl;
            cout << "idiv ebx" << endl;
            cout << "push edx" << endl;
            break;
        case LESS:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setl al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case LESS_EQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setle al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case GREATER:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setg al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case GREATER_EQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setge al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case EQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "sete al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case NOTEQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setne al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case BITWISE_AND:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "and eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case BITWISE_OR:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "or eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case BITWISE_XOR:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "xor eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case LOGICAL_AND:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "test eax, eax" << endl;
            cout << "jz zero" << zerocnt << endl;
            cout << "test ebx, ebx" << endl;
            cout << "jz zero" << zerocnt << endl;
            cout << "push 1" << endl;
            cout << "jmp logicalAndEnd" << zerocnt << endl;
            cout << "zero" << zerocnt << ":" << endl;
            cout << "push 0" << endl;
            cout << "logicalAndEnd" << zerocnt << ":" << endl;
            zerocnt++;
            break;
        case LOGICAL_OR:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "test eax, eax" << endl;
            cout << "jnz one" << onecnt << endl;
            cout << "test ebx, ebx" << endl;
            cout << "jnz one" << onecnt << endl;
            cout << "push 0" << endl;
            cout << "jmp logicalOrEnd" << onecnt << endl;
            cout << "one" << onecnt << ":" << endl;
            cout << "push 1" << endl;
            cout << "logicalOrEnd" << onecnt << ":" << endl;
            onecnt++;
            break;
        case ASSIGN:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "mov eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
    }
}

int main(int argc, char *argv[]){

    //ifstream file(argv[1]);
    ifstream file(R"(E:\CompilerLabs\Compilerlab3_copy\2.txt)");

    if (!file) {
        cerr << "Unable to open file!";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    yy_scan_string(content.c_str());
    lexing();
    // print();

    getFunctions();
    init();

    yy_scan_string(content.c_str());
    yyparse();

    return 0;
}