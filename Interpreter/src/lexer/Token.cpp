// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Token.h>

Token::Token(SourceLocation loc, TokenType type, string lexeme)
    : _loc(loc), _type(type), _lexeme(lexeme)
{

}

Token::Token(SourceLocation loc, TokenType type)
    : _loc(loc), _type(type)
{
    _lexeme = {};
}


SourceLocation Token::getLocation() const
{
    return _loc;
}

TokenType Token::getType() const
{
    return _type;
}

optional<string> Token::getLexeme() const
{
    return _lexeme;
}