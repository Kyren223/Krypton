// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <lexer/Token.h>
#include <vector>
#include <common/ErrorHandler.h>

using std::vector;

class Lexer
{
    ErrorHandler& _handler;
    vector<Token> _tokens;
    string _source;
    string _currentLine;
    SourceLocation _loc;
    size_t _start;
    size_t _current;
    bool _allowUtf8;
    size_t _utf8;
    
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
    
    string getUtf8Char();
    string unescape(const string& str);
    bool scanEscapeSequence(const string& str, string& result, size_t& i);
    static int getHex(char c);
    static int getOct(char c);
    static bool isDigit(char c);
};
