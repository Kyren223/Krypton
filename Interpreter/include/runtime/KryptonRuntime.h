// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <lexer/Token.h>
#include <nodes/ASTNode.h>
#include <nodes/Expressions.h>
#include <types/Value.h>
#include <memory>
#include <nodes/Statements.h>

using std::unique_ptr;

class KryptonRuntime
{
    unique_ptr<ASTNode> ast;
public:
    explicit KryptonRuntime(unique_ptr<ASTNode> ast);
    void run();
    
private:
    Value evaluate(const Expression& expression);
    Value evaluate(const BinaryExpression& expression);
    Value evaluate(const UnaryExpression& expression);
    void execute(const Statement& statement);
    void execute(const PrintStatement& statement);
    void execute(const CodeBlock& statement);
    void execute(const IfStatement& statement);
    [[nodiscard]] Value evaluate(const LiteralExpression& expression);
};
