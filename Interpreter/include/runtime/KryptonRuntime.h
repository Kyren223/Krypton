// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <lexer/Token.h>
#include <nodes/ASTNode.h>
#include <nodes/Expressions.h>
#include <types/Value.h>
#include <memory>

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
    [[nodiscard]] Value evaluate(const LiteralExpression& expression);
};
