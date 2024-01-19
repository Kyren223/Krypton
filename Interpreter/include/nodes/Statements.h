// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <nodes/ASTNode.h>
#include "Expressions.h"

struct Statement : ASTNode {};
struct InlineStatement : Statement {};

struct PrintStatement : InlineStatement
{
    unique_ptr<Expression> expression;

    explicit PrintStatement(unique_ptr<Expression> expression)
        : expression(std::move(expression)) {}
};

struct CodeBlock : InlineStatement
{
    vector<unique_ptr<Statement>> statements;

    explicit CodeBlock(vector<unique_ptr<Statement>> statements)
        : statements(std::move(statements)) {}
};

struct IfStatement : Statement
{
    unique_ptr<Expression> condition;
    unique_ptr<InlineStatement> thenBranch;
    optional<unique_ptr<InlineStatement>> elseBranch;

    IfStatement(unique_ptr<Expression> condition,
                unique_ptr<InlineStatement> thenBranch,
                unique_ptr<InlineStatement> elseBranch)
        : condition(std::move(condition)),
          thenBranch(std::move(thenBranch)),
          elseBranch(std::move(elseBranch)) {}
    
    IfStatement(unique_ptr<Expression> condition,
                unique_ptr<InlineStatement> thenBranch)
            : condition(std::move(condition)),
              thenBranch(std::move(thenBranch)),
              elseBranch(std::nullopt) {}
};
