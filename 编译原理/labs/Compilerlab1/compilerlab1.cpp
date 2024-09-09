#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <regex>
#include <unordered_map>
using namespace std;

int varCount = 0;
int assignCount = 0;
unordered_map<string, int> charCount;
unordered_map<string, int> charValue;

// 词法分析
enum TokenType
{
    INT,
    RETURN,
    IDENTIFIER,
    CONSTANT,
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    LPAREN, // ( 左括号
    RPAREN, // ) 右括号
    SEMICOLON // ; 分号
};

struct Token
{
    TokenType type;
    string value;
    int num;
};

vector<Token> lexer(string source)
{
    vector<Token> tokens;
    regex reg("\\s+");
    vector<string> words(sregex_token_iterator(source.begin(), source.end(), reg, -1), sregex_token_iterator());
    for (const auto& word : words)
    {
//        cout << word << endl;
        if (word == "int")
        {
            tokens.push_back({INT, word});
        }
        else if (word == "return")
        {
            tokens.push_back({RETURN, word});
        }
        else if (word == "=")
        {
            tokens.push_back({ASSIGN, word});
        }
        else if (word == "+")
        {
            tokens.push_back({ADD, word});
        }
        else if (word == "-")
        {
            tokens.push_back({SUB, word});
        }
        else if (word == "*")
        {
            tokens.push_back({MUL, word});
        }
        else if (word == "/")
        {
            tokens.push_back({DIV, word});
        }
        else if (word == "(")
        {
            tokens.push_back({LPAREN, word});
        }
        else if (word == ")")
        {
            tokens.push_back({RPAREN, word});
        }
        else if (word == ";")
        {
            tokens.push_back({SEMICOLON, word});
        }
        else if (regex_match(word, regex("[a-zA-Z]")))
        {
            tokens.push_back({IDENTIFIER, word});
        }
        else if (regex_match(word, regex("\\d+")))
        {
            tokens.push_back({CONSTANT, word});
        }
    }
    return tokens;
}

// 语法分析
void parse(vector<Token> &tokens)
{
    map<TokenType, int> priority = {
        {ASSIGN, 1},
        {ADD, 2},
        {SUB, 2},
        {MUL, 3},
        {DIV, 3},
        {LPAREN, 0},
        {RPAREN, 0},
        {SEMICOLON, 0}};
    stack<Token> opStack;
    stack<Token> numStack;
    bool minus = false;
    for (int i = 0; i < tokens.size(); i++)
    {
        Token token = tokens[i];
        if (token.type == INT)
        {
            varCount++;
            cout << "mov DWORD PTR [ebp-" << varCount * 4 << "], 0" << endl;
        }
        else if (token.type == RETURN)
        {
            Token ret_token = tokens[i+1];
            int ret_cnt = charCount[ret_token.value];
            cout << "mov eax, DWORD PTR [ebp-" << ret_cnt * 4 << "]" << endl;
//            cout << "最终结果是:  " << charValue[ret_token.value] << endl;
            return;
        }
        else if (token.type == IDENTIFIER)
        {
            if (charCount.find(token.value) == charCount.end()){
                charCount[token.value] = varCount;
            } else {
                token.num = charValue[token.value];
                if (!opStack.empty()){
                    cout << "mov eax, DWORD PTR [ebp-" << charCount[token.value] * 4 << "]" << endl;
                    if (minus){
                        token.num = -token.num;
                        charValue[token.value] = token.num;
                        minus = false;
                        cout << "neg eax" << endl;
                    }
                    cout << "push eax" << endl;
                }
                numStack.push(token);
            }
        }
        else if (token.type == CONSTANT)
        {
            token.num = stoi(token.value);
            if (minus){
                token.num = -token.num;
                minus = false;
                if (opStack.top().type != ASSIGN){
                    cout << "mov eax, " << token.num << endl;
                    cout << "push eax" << endl;
                }
            } else if (tokens[i+1].type != SEMICOLON || opStack.top().type != ASSIGN){
                cout << "mov eax, " << token.num << endl;
                cout << "push eax" << endl;
            }
            numStack.push(token);
        }
        else if (token.type == ASSIGN)
        {
            assignCount++;
            opStack.push(token);
        }
        else if (token.type == ADD || token.type == SUB || token.type == MUL || token.type == DIV)
        {
            if (opStack.empty() || priority[token.type] > priority[opStack.top().type])
            {
                if (token.type == SUB && tokens[i-1].type != IDENTIFIER && tokens[i-1].type != CONSTANT && tokens[i-1].type != RPAREN){
                    minus = true;
                    continue;
                }
                opStack.push(token);
            }
            else {
                while (!opStack.empty() && priority[token.type] <= priority[opStack.top().type]) {
                    auto op = opStack.top();
                    opStack.pop();
                    if (op.type == ADD) {
                        Token b = numStack.top();
                        numStack.pop();
                        Token a = numStack.top();
                        numStack.pop();
                        cout << "pop ebx" << endl;
                        cout << "pop eax" << endl;
                        cout << "add eax, ebx" << endl;
                        cout << "push eax" << endl;
                        Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num + b.num};
                        numStack.push(newToken);
                    } else if (op.type == SUB) {
                        Token b = numStack.top();
                        numStack.pop();
                        Token a = numStack.top();
                        numStack.pop();
                        cout << "pop ebx" << endl;
                        cout << "pop eax" << endl;
                        cout << "sub eax, ebx" << endl;
                        cout << "push eax" << endl;
                        Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num - b.num};
                        numStack.push(newToken);
                    } else if (op.type == MUL) {
                        Token b = numStack.top();
                        numStack.pop();
                        Token a = numStack.top();
                        numStack.pop();
                        cout << "pop ebx" << endl;
                        cout << "pop eax" << endl;
                        cout << "imul eax, ebx" << endl;
                        cout << "push eax" << endl;
                        Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num * b.num};
                        numStack.push(newToken);
                    } else if (op.type == DIV) {
                        Token b = numStack.top();
                        numStack.pop();
                        Token a = numStack.top();
                        numStack.pop();
                        cout << "pop ebx" << endl;
                        cout << "pop eax" << endl;
                        cout << "cdq" << endl;
                        cout << "idiv ebx" << endl;
                        cout << "push eax" << endl;
                        Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num / b.num};
                        numStack.push(newToken);
                    }
                }
                opStack.push(token);
            }
        }
        else if (token.type == LPAREN)
        {
            opStack.push(token);
        }
        else if (token.type == RPAREN)
        {
            while (true) {
                auto op = opStack.top();
                opStack.pop();
                if (op.type == ADD) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "add eax, ebx" << endl;
                    cout << "push eax" << endl;
                    Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num + b.num};
                    numStack.push(newToken);
                } else if (op.type == SUB) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "sub eax, ebx" << endl;
                    cout << "push eax" << endl;
                    Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num - b.num};
                    numStack.push(newToken);
                } else if (op.type == MUL) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "imul eax, ebx" << endl;
                    cout << "push eax" << endl;
                    Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num * b.num};
                    numStack.push(newToken);
                } else if (op.type == DIV) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "cdq" << endl;
                    cout << "idiv ebx" << endl;
                    cout << "push eax" << endl;
                    Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num / b.num};
                    numStack.push(newToken);
                } else if (op.type == LPAREN){
                    break;
                }
            }
        }
        else if (token.type == SEMICOLON) {
            while (!opStack.empty()) {
                auto op = opStack.top();
                opStack.pop();
                if (op.type == ADD) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    Token newToken;
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "add eax, ebx" << endl;
                    cout << "push eax" << endl;
                    newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num + b.num};
                    numStack.push(newToken);
                } else if (op.type == SUB) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    Token newToken;
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "sub eax, ebx" << endl;
                    cout << "push eax" << endl;
                    newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num - b.num};
                    numStack.push(newToken);
                } else if (op.type == MUL) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    Token newToken;
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "imul eax, ebx" << endl;
                    cout << "push eax" << endl;
                    newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num * b.num};
                    numStack.push(newToken);
                } else if (op.type == DIV) {
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    Token newToken;
                    cout << "pop ebx" << endl;
                    cout << "pop eax" << endl;
                    cout << "cdq" << endl;
                    cout << "idiv ebx" << endl;
                    cout << "push eax" << endl;
                    newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num / b.num};
                    numStack.push(newToken);
                }
                else if (op.type == ASSIGN){
                    Token b = numStack.top();
                    numStack.pop();
                    Token a = numStack.top();
                    numStack.pop();
                    if (b.type == IDENTIFIER){
                        cout << "pop eax" << endl;
                    }
                    a.num = b.num;
//                    cout << "赋值:  " << b.num << endl;
                    charValue[a.value] = a.num;
                    if (b.type == CONSTANT){
                        cout << "mov DWORD PTR [ebp-" << charCount[a.value] * 4 << "], " << a.num << endl;
                    } else {
                        cout << "mov DWORD PTR [ebp-" << charCount[a.value] * 4 << "], eax" << endl;
                    }
                    if (!opStack.empty()){
                        cout << "push eax" << endl;
                        Token newToken = {IDENTIFIER, "t" + to_string(varCount + 1), a.num};
                        numStack.push(newToken);
                    }
                }
            }
        }
    }
}


int main(int argc, char *argv[])
{
//    if (argc != 2)
//    {
//        cout << "Usage: " << argv[0] << " <input file>" << endl;
//        return 1;
//    }
//    ifstream file(argv[1]);
    ifstream file(R"(E:\CompilerLabs\Compilerlab1\input3.txt)");
    if (!file.is_open())
    {
        cout << "Error: cannot open file " << argv[1] << endl;
        return 1;
    }
    string source((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//    cout << source << endl << "---------------------" << endl;
    file.close();
    auto tokens = lexer(source);
    parse(tokens);
    return 0;
}