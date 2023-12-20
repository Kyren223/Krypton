// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <nodes/ASTNode.h>
#include <nodes/Expressions.h>

class PrettyPrinter
{
public:
    static void print(const ASTNode& node);
    static void print(const Expression& expr);
    static void print(const BinaryExpression& expr);
    static void print(const UnaryExpression& expr);
    static void print(const LiteralExpression& expr);
    
    static void printTokens(const vector<Token>& tokens);
};
