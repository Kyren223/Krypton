// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <lexer/Token.h>
#include <nodes/ASTNode.h>

struct Expression : ASTNode
{
    // TODO: Implement Type
};

struct LiteralExpression : Expression
{
    const Token& literal;
    explicit LiteralExpression(const Token& literal)
        : literal(literal) {}
};

struct UnaryExpression : Expression
{
    const Token& op;
    Expression* expression;
    explicit UnaryExpression(const Token& op, Expression* expression)
        : op(op), expression(expression) {}
};

struct BinaryExpression : Expression
{
    Expression* left;
    const Token& op;
    Expression* right;
    explicit BinaryExpression(Expression* left, const Token& op, Expression* right)
        : left(left), op(op), right(right) {}
};

struct TernaryExpression : Expression
{
    Expression* left;
    Expression* middle;
    Expression* right;
    explicit TernaryExpression(Expression* left, Expression* middle, Expression* right)
        : left(left), middle(middle), right(right) {}
};
