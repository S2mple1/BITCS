#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <unordered_map>
#include "tokens.hpp"

using namespace std;


extern int yylex();
extern void yy_scan_string(const char *str);
extern int yyparse();

void parse(vector<Token> vector1);

extern vector<Token> tokens;

void init(){
    cout << ".intel_syntax noprefix" << endl;
    cout << ".global main" << endl;
    cout << ".extern printf" << endl << endl;

    cout << ".data" << endl;
    cout << "format_str:" << endl;
    cout << R"(  .asciz "%d\n")" << endl << endl;

    cout << ".text" << endl;
    cout << "main:" << endl;
    cout << "  push ebp" << endl;
    cout << "  mov ebp, esp" << endl;
    cout << "  sub esp, 0x100" << endl << endl;
}

void parse(vector<Token> tokens) {

    map<TokenType, int> priority = {
            {TokenType::ADD, 6},
            {TokenType::SUB, 6},
            {TokenType::MUL, 7},
            {TokenType::DIV, 7},
            {TokenType::MOD, 7},
            {TokenType::LESS, 5},
            {TokenType::LESS_EQUAL, 5},
            {TokenType::GREATER, 5},
            {TokenType::GREATER_EQUAL, 5},
            {TokenType::EQUAL, 4},
            {TokenType::NOTEQUAL, 4},
            {TokenType::AND, 3},
            {TokenType::OR, 1},
            {TokenType::XOR, 2},
            {TokenType::ASSIGN, 0},
            {TokenType::LPAREN, -1},
            {TokenType::RPAREN, -1},
    };

    stack<Token> opStack;
    stack<Token> valStack;
    unordered_map<string, int> values;
    unordered_map<string, int> count;
    int nums = 0;
    int ops;
    bool mainBody = false;
    bool print = false;
    bool define = false;
    bool ret = false;
    bool minus = false;

    init();

    for (int i = 0; i < tokens.size(); i++) {
        Token token = tokens[i];
        if (token.type == TokenType::LEFT_PARENTHESIS){
            mainBody = true;
            continue;
        }
        if (!mainBody){
            continue;
        }
        if (token.type == TokenType::INT) {
            nums++;
            define = true;
        } else if (token.type == TokenType::NUMBER) {
//            if (tokens[i+1].type == LESS || tokens[i+1].type == LESS_EQUAL || tokens[i+1].type == GREATER || tokens[i+1].type == GREATER_EQUAL || tokens[i+1].type == EQUAL || tokens[i+1].type == NOTEQUAL || tokens[i-1].type == LESS_EQUAL || tokens[i-1].type == GREATER_EQUAL || tokens[i-1].type == LESS || tokens[i-1].type == GREATER || tokens[i-1].type == EQUAL || tokens[i-1].type == NOTEQUAL){
//                token.value = stoi(token.name);
//                valStack.push(token);
//                continue;
//            }
            if (ret){
                cout << "  mov eax, " << token.value << endl;
                cout << "  leave" << endl;
                cout << "  ret" << endl;
                break;
            }
            token.value = stoi(token.name);
            if (minus) {
                token.value = -token.value;
                minus = false;
            }
            if (tokens[i-1].type != ASSIGN || tokens[i+1].type != SEMICOLON){
                cout << "  mov eax, " << token.value << endl;
                cout << "  push eax" << endl << endl;
            }
            valStack.push(token);
        } else if (token.type == RETURN) {
            ret = true;
        } else if (token.type == TokenType::SEMICOLON){
            if (print){
                print = false;
                cout << "  push offset format_str" << endl;
                cout << "  call printf" << endl;
                cout << "  add esp, 8" << endl << endl;
                continue;
            }
            if (define){
                define = false;
                continue;
            }
            ops = opStack.size();
            while (!opStack.empty()) {
                Token op = opStack.top();
                opStack.pop();
                Token val2 = valStack.top();
                valStack.pop();
                Token val1 = valStack.top();
                valStack.pop();
                Token newToken;
                if (op.type == ADD) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  add eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value + val2.value};
                    valStack.push(newToken);
                } else if (op.type == SUB) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  sub eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value - val2.value};
                    valStack.push(newToken);
                } else if (op.type == MUL) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  imul eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value * val2.value};
                    valStack.push(newToken);
                } else if (op.type == DIV) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  cdq" << endl;
                    cout << "  idiv ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value / val2.value};
                    valStack.push(newToken);
                } else if (op.type == MOD) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  cdq" << endl;
                    cout << "  idiv ebx" << endl;
                    cout << "  push edx" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value % val2.value};
                    valStack.push(newToken);
                } else if (op.type == LESS) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value < val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " < " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == LESS_EQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value <= val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " <= " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == GREATER) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value > val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " > " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == GREATER_EQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value >= val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " >= " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == EQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value == val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " == " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == NOTEQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value != val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " != " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == AND) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  and eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value & val2.value};
                    valStack.push(newToken);
                } else if (op.type == OR) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  or eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value | val2.value};
                    valStack.push(newToken);
                } else if (op.type == XOR) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  xor eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value ^ val2.value};
                    valStack.push(newToken);
                } else if (op.type == ASSIGN){
                    if (ops == 1){
                        if (val2.type == IDENTIFIER){
                            cout << "  mov eax, DWORD PTR [ebp-" << count[val2.name] * 4 << "]" << endl;
                        } else if (val2.type == NUMBER){
                            cout << "  mov eax, " << val2.value << endl;
                        }
                        cout << "  mov DWORD PTR [ebp-" << count[val1.name] * 4 << "], eax" << endl << endl;
                    } else {
                        if (val2.type == NUMBER){
                            cout << "  mov DWORD PTR [ebp-" << count[val1.name] * 4 << "], " << val2.value << endl;
                        } else {
                            cout << "  pop eax" << endl;
                            cout << "  mov DWORD PTR [ebp-" << count[val1.name] * 4 << "], eax" << endl;
                        }
                        if (!opStack.empty()){
                            cout << "push eax" << endl;
                            newToken = {IDENTIFIER, "t" + to_string(nums + 1), val2.value};
                            valStack.push(newToken);
                        }
                    }
                    val1.value = val2.value;
                    values[val1.name] = val1.value;
                }
            }
            ops = 0;
        } else if (token.type == PREDEFINED_FUNCTION){
            print = true;
        } else if (token.type == IDENTIFIER){
//            if (tokens[i-1].type == LESS_EQUAL || tokens[i-1].type == GREATER_EQUAL || tokens[i-1].type == LESS || tokens[i-1].type == GREATER || tokens[i-1].type == EQUAL || tokens[i-1].type == NOTEQUAL || tokens[i+1].type == LESS || tokens[i+1].type == LESS_EQUAL || tokens[i+1].type == GREATER || tokens[i+1].type == GREATER_EQUAL || tokens[i+1].type == EQUAL || tokens[i+1].type == NOTEQUAL){
//                token.value = values[token.name];
//                valStack.push(token);
//                continue;
//            }
            if (ret){
                cout << "  mov eax, DWORD PTR [ebp-" << count[token.name] * 4 << "]" << endl;
                cout << "  leave" << endl;
                cout << "  ret" << endl;
                break;
            }
            if (print){
                cout << "  push DWORD PTR [ebp-" << count[token.name] * 4 << "]" << endl;
                continue;
            }
            if (define){
                count[token.name] = nums;
                continue;
            }
            token.value = values[token.name];
            if (!opStack.empty() && (tokens[i+1].type != SEMICOLON || opStack.top().type != ASSIGN)){
                cout << "  mov eax, DWORD PTR [ebp-" << count[token.name] * 4 << "]" << endl;
                if (minus){
                    token.value = -token.value;
                    values[token.name] = token.value;
                    minus = false;
                    cout << "neg eax" << endl;
                }
                cout << "  push eax" << endl << endl;
            }
            valStack.push(token);
        } else if (token.type == ADD || token.type == SUB || token.type == MUL ||
                   token.type == DIV || token.type == MOD || token.type == LESS ||
                   token.type == LESS_EQUAL || token.type == GREATER || token.type == ASSIGN ||
                   token.type == GREATER_EQUAL || token.type == EQUAL ||
                   token.type == NOTEQUAL || token.type == AND || token.type == OR ||
                   token.type == XOR) {
            if (opStack.empty() || priority[token.type] > priority[opStack.top().type])
            {
                if (token.type == SUB && tokens[i-1].type != IDENTIFIER && tokens[i-1].type != NUMBER && tokens[i-1].type != RPAREN){
                    minus = true;
                    continue;
                }
                opStack.push(token);
            }
            else {
                while (!opStack.empty() && priority[token.type] <= priority[opStack.top().type]) {
                    auto op = opStack.top();
                    opStack.pop();
                    Token val2 = valStack.top();
                    valStack.pop();
                    Token val1 = valStack.top();
                    valStack.pop();
                    Token newToken;
                    if (op.type == ADD) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  add eax, ebx" << endl;
                        cout << "  push eax" << endl << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value + val2.value};
                        valStack.push(newToken);
                    } else if (op.type == SUB) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  sub eax, ebx" << endl;
                        cout << "  push eax" << endl << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value - val2.value};
                        valStack.push(newToken);
                    } else if (op.type == MUL) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  imul eax, ebx" << endl << endl;
                        cout << "  push eax" << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value * val2.value};
                        valStack.push(newToken);
                    } else if (op.type == DIV) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  cdq" << endl;
                        cout << "  idiv ebx" << endl;
                        cout << "  push eax" << endl << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value / val2.value};
                        valStack.push(newToken);
                    } else if (op.type == MOD) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  cdq" << endl;
                        cout << "  idiv ebx" << endl;
                        cout << "  push edx" << endl << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value % val2.value};
                        valStack.push(newToken);
                    } else if (op.type == LESS) {
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value < val2.value ? 1 : 0};
                        valStack.push(newToken);
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
//                        if (opStack.top().type != ASSIGN) {
                            cout << "  mov eax, " << newToken.value << endl;
                            cout << "  push eax" << endl;
//                        }
                    } else if (op.type == LESS_EQUAL) {
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value <= val2.value ? 1 : 0};
                        valStack.push(newToken);
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
//                        if (opStack.top().type != ASSIGN) {
                            cout << "  mov eax, " << newToken.value << endl;
                            cout << "  push eax" << endl;
//                        }
                    } else if (op.type == GREATER) {
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value > val2.value ? 1 : 0};
                        valStack.push(newToken);
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
//                        if (opStack.top().type != ASSIGN) {
                            cout << "  mov eax, " << newToken.value << endl;
                            cout << "  push eax" << endl;
//                        }
                    } else if (op.type == GREATER_EQUAL) {
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value >= val2.value ? 1 : 0};
                        valStack.push(newToken);
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
//                        if (opStack.top().type != ASSIGN) {
                            cout << "  mov eax, " << newToken.value << endl;
                            cout << "  push eax" << endl;
//                        }
                    } else if (op.type == EQUAL) {
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value == val2.value ? 1 : 0};
                        valStack.push(newToken);
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
//                        if (opStack.top().type != ASSIGN) {
                            cout << "  mov eax, " << newToken.value << endl;
                            cout << "  push eax" << endl;
//                        }
                    } else if (op.type == NOTEQUAL) {
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value != val2.value ? 1 : 0};
                        valStack.push(newToken);
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
//                        cout << val1.value << "!=" << val2.value << endl;
//                        if (opStack.top().type != ASSIGN) {
                            cout << "  mov eax, " << newToken.value << endl;
                            cout << "  push eax" << endl;
//                        }
                    } else if (op.type == AND) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  and eax, ebx" << endl;
                        cout << "  push eax" << endl << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value & val2.value};
                        valStack.push(newToken);
                    } else if (op.type == OR) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  or eax, ebx" << endl;
                        cout << "  push eax" << endl << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value | val2.value};
                        valStack.push(newToken);
                    } else if (op.type == XOR) {
                        cout << "  pop ebx" << endl;
                        cout << "  pop eax" << endl;
                        cout << "  xor eax, ebx" << endl;
                        cout << "  push eax" << endl << endl;
                        newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value ^ val2.value};
                        valStack.push(newToken);
                    }
                }
                opStack.push(token);
            }
        } else if (token.type == LPAREN)
        {
            if (print){
                continue;
            }
            opStack.push(token);
        }
        else if (token.type == RPAREN)
        {
            if (print){
                continue;
            }
            while (true) {
                Token op = opStack.top();
                opStack.pop();
                if (op.type == LPAREN) {
                    break;
                }
                Token val2 = valStack.top();
                valStack.pop();
                Token val1 = valStack.top();
                valStack.pop();
                Token newToken;
                if (op.type == ADD) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  add eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value + val2.value};
                    valStack.push(newToken);
                } else if (op.type == SUB) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  sub eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value - val2.value};
                    valStack.push(newToken);
                } else if (op.type == MUL) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  imul eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value * val2.value};
                    valStack.push(newToken);
                } else if (op.type == DIV) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  cdq" << endl;
                    cout << "  idiv ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value / val2.value};
                    valStack.push(newToken);
                }  else if (op.type == MOD) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  cdq" << endl;
                    cout << "  idiv ebx" << endl;
                    cout << "  push edx" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value % val2.value};
                    valStack.push(newToken);
                } else if (op.type == LESS) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value < val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == LESS_EQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value <= val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == GREATER) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value > val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " > " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == GREATER_EQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value >= val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " >= " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == EQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value == val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " == " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == NOTEQUAL) {
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value != val2.value ? 1 : 0};
                    valStack.push(newToken);
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
//                    cout << val1.value << " != " << val2.value << endl;
//                    if (opStack.top().type != ASSIGN) {
                        cout << "  mov eax, " << newToken.value << endl;
                        cout << "  push eax" << endl;
//                    }
                } else if (op.type == AND) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  and eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value & val2.value};
                    valStack.push(newToken);
                } else if (op.type == OR) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  or eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value | val2.value};
                    valStack.push(newToken);
                } else if (op.type == XOR) {
                    cout << "  pop ebx" << endl;
                    cout << "  pop eax" << endl;
                    cout << "  xor eax, ebx" << endl;
                    cout << "  push eax" << endl << endl;
                    newToken = {IDENTIFIER, "t" + to_string(nums + 1), val1.value ^ val2.value};
                    valStack.push(newToken);
                }
            }
        }
    }
}


int main(int argc, char *argv[]) {

//    if (argc != 2)
//    {
//        cout << "Usage: " << argv[0] << " <input file>" << endl;
//        return 1;
//    }
//    ifstream file(argv[1]);

    ifstream file(R"(E:\CompilerLabs\Compilerlab3\1.txt)");

    if (!file) {
        cerr << "Unable to open file!";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    yy_scan_string(content.c_str());

//    yylex();

//    for (const auto& token : tokens) {
//        cout << "Token type: " << token.type << ", value: " << token.name << endl;
//    }
//    cout << "-------------------------------------------" << endl;

//    parse(tokens);
    yyparse();

    file.close();
    return 0;
}