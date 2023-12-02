// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <vector>
#include <lexer/Lexer.h>
#include <nodes/ASTNode.h>

using std::vector;

class Parser
{
protected:
    Lexer& _lexer;
public:
    virtual ASTNode* parse(Lexer& lexer) = 0;
};
