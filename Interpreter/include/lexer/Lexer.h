// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once


#include "Token.h"

class Lexer
{
public:
    Token next();
    Token peek();
};
