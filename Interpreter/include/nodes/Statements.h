// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <nodes/ASTNode.h>
#include <types/Type.h>
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
    bool hasScope = true;

    explicit CodeBlock(vector<unique_ptr<Statement>> statements)
        : statements(std::move(statements)) {}
        
    explicit CodeBlock(vector<unique_ptr<Statement>> statements, bool scope)
            : statements(std::move(statements)), hasScope(scope) {}
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

struct VariableDeclaration : Statement
{
    optional<const Type*> type;
    string identifier;
    optional<unique_ptr<Expression>> initializer;
    
    VariableDeclaration(optional<const Type*> type,
                        const Token& identifier,
                        unique_ptr<Expression> initializer)
        : type(type),
          identifier(identifier.getLexeme().value()),
          initializer(std::move(initializer)) {}
  
    VariableDeclaration(optional<const Type*> type,
                        const Token& identifier)
        : type(type),
          identifier(identifier.getLexeme().value()),
          initializer(std::nullopt) {}
};

struct VariableAssignment : Statement
{
    string identifier;
    unique_ptr<Expression> value;
    
    VariableAssignment(const Token& identifier,
                       unique_ptr<Expression> value)
        : identifier(identifier.getLexeme().value()),
          value(std::move(value)) {}
};

struct WhileStatement : Statement
{
    unique_ptr<Expression> condition;
    unique_ptr<InlineStatement> body;
    
    WhileStatement(unique_ptr<Expression> condition,
                   unique_ptr<InlineStatement> body)
        : condition(std::move(condition)),
          body(std::move(body)) {}
};
