// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <lexer/Token.h>
#include <nodes/ASTNode.h>
#include <memory>

using std::unique_ptr;

struct Expression : ASTNode
{

};

struct LiteralExpression : Expression
{
    // TODO: Implement Type
    const Token& literal;
    explicit LiteralExpression(const Token& literal)
        : literal(literal) {}
};

struct UnaryExpression : Expression
{
    const Token& op;
    unique_ptr<Expression> expression;
    UnaryExpression(const Token& op, unique_ptr<Expression> expression)
        : op(op), expression(std::move(expression)) {}
};

struct BinaryExpression : Expression
{
    unique_ptr<Expression> left;
    const Token& op;
    unique_ptr<Expression> right;
    explicit BinaryExpression(unique_ptr<Expression> left, const Token& op, unique_ptr<Expression> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
};

struct TernaryExpression : Expression
{
    unique_ptr<Expression> left;
    unique_ptr<Expression> middle;
    unique_ptr<Expression> right;
    explicit TernaryExpression(unique_ptr<Expression> left, unique_ptr<Expression> middle, unique_ptr<Expression> right)
        : left(std::move(left)), middle(std::move(middle)), right(std::move(right)) {}
};
