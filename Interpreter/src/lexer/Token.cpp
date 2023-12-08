// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Token.h>

#include <utility>

Token::Token(Location location, TokenType type, string lexeme)
    : _location(std::move(location)), _type(type), _lexeme(std::move(lexeme))
{

}

Location Token::getLocation() const
{
    return _location;
}

TokenType Token::getType() const
{
    return _type;
}

string Token::getLexeme() const
{
    return _lexeme;
}

Location::Location(const fs::path& fullPath, int line, int column, int length)
{
    _fullPath = fullPath.string();
    _fileName = fullPath.filename().string();
    _line = line;
    _column = column;
    _length = length;
}

string Location::getFullPath() const
{
    return _fullPath;
}

string Location::getFileName() const
{
    return _fileName;
}

int Location::getLine() const
{
    return _line;
}

int Location::getColumn() const
{
    return _column;
}

int Location::getLength() const
{
    return _length;
}
