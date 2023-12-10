// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <lexer/Token.h>
#include <vector>

using std::vector;

class Lexer
{
    vector<Token> _tokens;
    string _source;
    SourceLocation _loc;
    int _start;
    int _current;
    
public:
    Lexer(const string& filepath, const string& source);
    vector<Token> scanTokens();
    
private:
    bool isAtEnd();
    void addToken(TokenType type);
    void addToken(TokenType type, const string& lexeme);
    
    char advance();
    char peek();
    char peekNext();
    
    void scanToken();
    bool match(char expected);
    
    void scanComment();
    void scanMultilineComment();
    void scanString();
    void scanChar();
    void scanNumber();
    
    static bool isDigit(char c);
};
