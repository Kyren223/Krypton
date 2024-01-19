// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <lexer/Token.h>
#include <nodes/ASTNode.h>
#include <memory>
#include <utility>

using std::unique_ptr;

struct Expression : ASTNode {};

struct LiteralExpression : Expression
{
    const Token literal;
    explicit LiteralExpression(Token  literal)
        : literal(std::move(literal)) {}
};

struct UnaryExpression : Expression
{
    const Token op;
    unique_ptr<Expression> expression;
    UnaryExpression(Token op, unique_ptr<Expression> expression)
        : op(std::move(op)), expression(std::move(expression)) {}
};

struct BinaryExpression : Expression
{
    unique_ptr<Expression> left;
    const Token op;
    unique_ptr<Expression> right;
    explicit BinaryExpression(unique_ptr<Expression> left, Token op, unique_ptr<Expression> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}
};

struct TernaryExpression : Expression
{
    unique_ptr<Expression> left;
    unique_ptr<Expression> middle;
    unique_ptr<Expression> right;
    explicit TernaryExpression(unique_ptr<Expression> left, unique_ptr<Expression> middle, unique_ptr<Expression> right)
        : left(std::move(left)), middle(std::move(middle)), right(std::move(right)) {}
};
