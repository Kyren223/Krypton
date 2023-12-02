// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>

using std::string;

enum class TokenType
{

};

struct Token
{
    TokenType type;
    string lexeme;
};
