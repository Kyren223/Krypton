// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <utility>
#include <filesystem>
#include <optional>
#include <common/ErrorHandler.h>

namespace fs = std::filesystem;
using std::string, std::optional;


enum class TokenTypes
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
    DOT,
    BACK_SLASH,
    AT,
    DOLLAR,
    HASHTAG,
    
    // One or two character tokens
    BANG,
    EQUAL,
    GREATER,
    LESS,
    PIPE,
    AMPERSAND,
    PERCENT,
    CARET,
    SLASH,
    ASTERISK,
    PLUS,
    MINUS,
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
    PIPE_PIPE,
    AMPERSAND_AMPERSAND,
    PLUS_PLUS,
    MINUS_MINUS,
    
    
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
    NUL, // null
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
    PRINT, // TODO: Remove this (temporary)
    
    // Built-in type keywords
    VOID, // void*
    BOOL, // bool 1-bit
    CHAR, // char 1-byte
    INT, // int 4-bytes
    DEC, // double 8-bytes
    
    END
};

class Token
{
    SourceLocation _loc;
    TokenTypes _type;
    optional<string> _lexeme;
    
public:
    Token(SourceLocation loc, TokenTypes type, string lexeme);
    Token(SourceLocation loc, TokenTypes type);
    
    [[nodiscard]] SourceLocation getLocation() const;
    [[nodiscard]] TokenTypes getType() const;
    [[nodiscard]] optional<string> getLexeme() const;
    [[nodiscard]] string toString();
    
    static string getTokenTypeString(TokenTypes type);
};
