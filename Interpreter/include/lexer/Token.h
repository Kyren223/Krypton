// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <utility>
#include <filesystem>

namespace fs = std::filesystem;
using std::string;


enum class TokenType
{
    // Single-character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    COLON,
    SEMICOLON,
    QUESTION_MARK,
    BANG,
    DOT,
    MINUS,
    PLUS,
    ASTERISK,
    SLASH,
    CARET,
    PERCENTAGE,
    AMPERSAND,
    PIPE,
    GREATER,
    LESS,
    EQUAL,
    BACK_SLASH,
    AT,
    DOLLAR,
    HASHTAG,
    
    // Two-character tokens
    BANG_EQUAL,
    EQUAL_EQUAL,
    GREATER_EQUAL,
    LESS_EQUAL,
    PIPE_EQUAL,
    AMPERSAND_EQUAL,
    PERCENTAGE_EQUAL,
    CARET_EQUAL,
    SLASH_EQUAL,
    ASTERISK_EQUAL,
    PLUS_EQUAL,
    MINUS_EQUAL,
    GREATER_GREATER,
    LESS_LESS,
    PIPE_PIPE,
    AMPERSAND_AMPERSAND,
    PLUS_PLUS,
    MINUS_MINUS,
    
    // Three-character tokens
    GREATER_GREATER_EQUAL,
    LESS_LESS_EQUAL,
    
    
    // Literals
    IDENTIFIER,
    CHAR_LITERAL,
    STRING_LITERAL,
    INT_LITERAL,
    DEC_LITERAL,
    
    // Keywords
    CLASS,
    IS,
    IF,
    ELSE,
    FOR,
    WHILE,
    TRUE,
    FALSE,
    SUPER,
    THIS,
    RETURN,
    BREAK,
    CONTINUE,
    NULL_,
    IMPORT,
    AS,
    FROM,
    SWITCH,
    CASE,
    DEFAULT,
    ENUM,
    EXPORT,
    AND,
    OR,
    
    // Built-in type keywords
    VOID, // void*
    BOOL, // bool 1-bit
    CHAR, // char 1-byte
    INT, // int 4-bytes
    DEC, // double 8-bytes
};

class Location
{
    string _fullPath;
    string _fileName;
    int _line;
    int _column;
    int _length;
    
public:
    Location(const fs::path& fullPath, int line, int column, int length);

    [[nodiscard]] string getFullPath() const;
    [[nodiscard]] string getFileName() const;
    [[nodiscard]] int getLine() const;
    [[nodiscard]] int getColumn() const;
    [[nodiscard]] int getLength() const;
};

class Token
{
    Location _location;
    TokenType _type;
    string _lexeme;
    
public:
    Token(Location location, TokenType type, string lexeme);
    
    [[nodiscard]] Location getLocation() const;
    [[nodiscard]] TokenType getType() const;
    [[nodiscard]] string getLexeme() const;
};
