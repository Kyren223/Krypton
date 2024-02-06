// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <nodes/Expressions.h>
#include <nodes/Statements.h>
#include <runtime/Environment.h>

#include <functional>
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
    optional<optional<const Type*>> returnType;
    vector<pair<string, optional<const Type*>>> parameters;
    unique_ptr<CodeBlock> body;
    function<void(Environment*)> nativeFunction;
    bool isNative;
    explicit LambdaExpression(optional<const Type*> returnType, vector<pair<string, optional<const Type*>>> parameters, unique_ptr<CodeBlock> body)
            : returnType(returnType), parameters(std::move(parameters)), body(std::move(body)), isNative(false) {}
    explicit LambdaExpression(vector<pair<string, optional<const Type*>>> parameters, unique_ptr<CodeBlock> body)
            : returnType(std::nullopt), parameters(std::move(parameters)), body(std::move(body)), isNative(false)  {}
    explicit LambdaExpression(const Type* returnType, vector<pair<string, optional<const Type*>>> parameters, function<void(Environment*)> nativeFunction)
            : returnType(returnType), parameters(std::move(parameters)), nativeFunction(std::move(nativeFunction)), isNative(true) {}
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
