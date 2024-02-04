// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <nodes/Expressions.h>
#include <nodes/Statements.h>

#include <utility>

struct CallExpression : Expression
{
    unique_ptr<Expression> callee;
    vector<unique_ptr<Expression>> arguments;
    explicit CallExpression(unique_ptr<Expression> callee, vector<unique_ptr<Expression>> arguments)
            : callee(std::move(callee)), arguments(std::move(arguments)) {}
};

struct LambdaExpression : Expression
{
    optional<const Type*> returnType;
    vector<pair<string, const Type*>> parameters;
    unique_ptr<CodeBlock> body;
    explicit LambdaExpression(const Type* returnType, vector<pair<string, const Type*>> parameters, unique_ptr<CodeBlock> body)
            : returnType(returnType), parameters(std::move(parameters)), body(std::move(body)) {}
    explicit LambdaExpression(vector<pair<string, const Type*>> parameters, unique_ptr<CodeBlock> body)
            : returnType(std::nullopt), parameters(std::move(parameters)), body(std::move(body)) {}
};

struct CallStatement : InlineStatement
{
    unique_ptr<CallExpression> call;
    explicit CallStatement(unique_ptr<CallExpression> call) : call(std::move(call)) {}
};

struct ReturnStatement : InlineStatement
{
    optional<unique_ptr<Expression>> value;
    explicit ReturnStatement(unique_ptr<Expression> value) : value(std::move(value)) {}
    explicit ReturnStatement() : value(std::nullopt) {}
};
