// Copyright (c) 2023 Krypton. All rights reserved.
#include <runtime/KryptonRuntime.h>

#include <common/Logger.h>
#include <lexer/Token.h>

KryptonRuntime::KryptonRuntime(unique_ptr<ASTNode> ast)
{
    this->ast = std::move(ast);
}

void KryptonRuntime::run()
{
    if (auto node = dynamic_cast<const Expression*>(ast.get()))
    {
        Value value = evaluate(*node);
        if (&value.getType() == &Primitive::INT)
        {
            int result = value.getValue<int>();
            Logger::print(LogMode::NONE, std::to_string(result) + "\n", Color::BLUE);
        }
        else if (&value.getType() == &Primitive::DEC)
        {
            double result = value.getValue<double>();
            Logger::print(LogMode::NONE, std::to_string(result) + "\n", Color::BLUE);
        }
        else if (&value.getType() == &Primitive::BOOL)
        {
            bool result = value.getValue<bool>();
            Logger::print(LogMode::NONE, std::to_string(result) + "\n", Color::BLUE);
        }
    }
}

Value KryptonRuntime::evaluate(const Expression& expression)
{
    if (auto pBinary = dynamic_cast<const BinaryExpression*>(&expression))
    {
        return evaluate(*pBinary);
    }
    else if (auto pUnary = dynamic_cast<const UnaryExpression*>(&expression))
    {
        return evaluate(*pUnary);
    }
    else if (auto pLiteral = dynamic_cast<const LiteralExpression*>(&expression))
    {
        return evaluate(*pLiteral);
    }
    else
    {
        // TODO: Add better error handling
        Logger::error("KryptonRuntime::evaluate - unknown expression type");
        exit(1);
    }
}

Value KryptonRuntime::evaluate(const BinaryExpression& expression)
{
    Value left = evaluate(*expression.left);
    Value right = evaluate(*expression.right);
    Operation::Binary operation = Operation::getBinaryOperation(expression.op.getType());
    return left.getType().binaryOperation(operation, left, right);
}

Value KryptonRuntime::evaluate(const UnaryExpression& expression)
{
    Value value = evaluate(*expression.expression);
    Operation::Unary operation = Operation::getUnaryOperation(expression.op.getType());
    return value.getType().unaryOperation(operation, value);
}

Value KryptonRuntime::evaluate(const LiteralExpression& expression)
{
    switch (expression.literal.getType())
    {
        case TokenTypes::INT_LITERAL:
        {
            int value = std::stoi(expression.literal.getLexeme().value());
            return {Primitive::INT, value};
        }
        case TokenTypes::DEC_LITERAL:
        {
            double value = std::stod(expression.literal.getLexeme().value());
            return {Primitive::DEC, value};
        }
        default: break;
    }
    // TODO: Add better error handling
    Logger::error("KryptonRuntime::evaluate - unknown literal type");
    exit(1);
}

