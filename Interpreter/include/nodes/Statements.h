// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <nodes/ASTNode.h>
#include "Expressions.h"

struct Statement : ASTNode
{

};

struct PrintStatement : Statement
{
    unique_ptr<Expression> expression;

    explicit PrintStatement(unique_ptr<Expression> expression)
        : expression(std::move(expression)) {}
};

struct ScopeStatement : Statement
{
    vector<unique_ptr<Statement>> statements;

    explicit ScopeStatement(vector<unique_ptr<Statement>> statements)
        : statements(std::move(statements)) {}
};

struct IfStatement : Statement
{
    unique_ptr<Expression> condition;
    unique_ptr<Statement> thenBranch;
    optional<unique_ptr<Statement>> elseBranch;

    IfStatement(unique_ptr<Expression> condition,
                unique_ptr<Statement> thenBranch,
                unique_ptr<Statement> elseBranch)
        : condition(std::move(condition)),
          thenBranch(std::move(thenBranch)),
          elseBranch(std::move(elseBranch)) {}
    
    IfStatement(unique_ptr<Expression> condition,
                unique_ptr<Statement> thenBranch)
            : condition(std::move(condition)),
              thenBranch(std::move(thenBranch)),
              elseBranch(std::nullopt) {}
};
