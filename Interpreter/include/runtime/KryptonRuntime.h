// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <lexer/Token.h>
#include <nodes/ASTNode.h>
#include <nodes/Expressions.h>
#include <types/Value.h>
#include <memory>
#include <nodes/Statements.h>
#include "Environment.h"

using std::unique_ptr;

class KryptonRuntime
{
    unique_ptr<ASTNode> _ast;
    Environment& _environment;
    ErrorHandler& _handler;
    
public:
    explicit KryptonRuntime(unique_ptr<ASTNode> ast, Environment& environment);
    void run();
    
private:
    Value evaluate(const Expression& expression);
    Value evaluate(const BinaryExpression& expression);
    Value evaluate(const UnaryExpression& expression);
    Value evaluate(const LiteralExpression& expression);
    void execute(const Statement& statement);
    void execute(const PrintStatement& statement);
    void execute(const CodeBlock& statement);
    void execute(const IfStatement& statement);
    void execute(const VariableDeclaration& statement);
    void execute(const VariableAssignment& statement);
};
