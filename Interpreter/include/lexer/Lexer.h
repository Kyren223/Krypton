// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <lexer/Token.h>
#include <vector>
#include <common/ErrorHandler.h>
#include <unordered_map>

using std::vector, std::unordered_map;

class Lexer
{
    static const unordered_map<string, TokenTypes> KEYWORDS;
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
    Lexer(const string& filepath, string source);
    vector<Token> scanTokens();
    
private:
    bool isAtEnd();
    void addToken(TokenTypes type);
    void addToken(TokenTypes type, const string& lexeme);
    
    char consume();
    char peek();
    char peekNext();
    
    void scanToken();
    bool match(char expected);
    
    void scanComment();
    void scanMultilineComment();
    void scanString();
    void scanChar();

    void scanNumber();
    void scanIdentifier();
    
    string getUtf8Char();
    string unescape(const string& str);
    bool scanEscapeSequence(const string& str, string& result, size_t& i);
    static int getHex(char c);
    static int getOct(char c);
    static int getBin(char c);
    static bool isDigit(char c);
    static bool isIdentifier(char c);
    static bool isIdentifierStart(char c);
};
