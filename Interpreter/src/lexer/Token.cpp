// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Token.h>

Token::Token(FilePosition pos, TokenType type, string lexeme)
    : _pos(pos), _type(type), _lexeme(lexeme)
{

}

Token::Token(FilePosition pos, TokenType type)
    : _pos(pos), _type(type)
{
    _lexeme = {};
}


FilePosition Token::getLocation() const
{
    return _pos;
}

TokenType Token::getType() const
{
    return _type;
}

optional<string> Token::getLexeme() const
{
    return _lexeme;
}