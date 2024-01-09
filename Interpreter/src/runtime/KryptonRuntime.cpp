// Copyright (c) 2023 Krypton. All rights reserved.
#include <runtime/KryptonRuntime.h>

#include <common/Logger.h>
#include <lexer/Token.h>
#include <nodes/Statements.h>

KryptonRuntime::KryptonRuntime(unique_ptr<ASTNode> ast)
{
    this->ast = std::move(ast);
}

void KryptonRuntime::run()
{
    if (auto node = dynamic_cast<const Statement*>(ast.get()))
    {
        execute(*node);
    }
    else if (auto node = dynamic_cast<const Expression*>(ast.get()))
    {
        //evaluate(*node);
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
    
    // Comparison operators
    switch (expression.op.getType())
    {
        case TokenTypes::EQUAL_EQUAL:
        {
            return left.getType().isEqual(left, right);
        }
        
        case TokenTypes::BANG_EQUAL:
        {
            bool isNotEqual = !left.getType().isEqual(left, right).getValue<bool>();
            return {Primitive::BOOL, isNotEqual};
        }
        
        case TokenTypes::GREATER:
        {
            return left.getType().compare(left, right);
        }
        
        case TokenTypes::GREATER_EQUAL:
        {
            Value isEqual = left.getType().isEqual(left, right);
            Value isGreater = left.getType().compare(left, right);
            bool isGreaterEqual = isEqual.getValue<bool>() || isGreater.getValue<bool>();
            return {Primitive::BOOL, isGreaterEqual};
        }
        
        case TokenTypes::LESS:
        {
            Value isEqual = left.getType().isEqual(left, right);
            Value isGreater = left.getType().compare(left, right);
            bool isLess = !(isEqual.getValue<bool>() || isGreater.getValue<bool>());
            return {Primitive::BOOL, isLess};
        }
        
        case TokenTypes::LESS_EQUAL:
        {
            Value isGreater = left.getType().isEqual(left, right);
            bool isLessEqual = !isGreater.getValue<bool>();
            return {Primitive::BOOL, isLessEqual};
        }
        
        default:
        {
            Operation::Binary operation = Operation::getBinaryOperation(expression.op.getType());
            return left.getType().binaryOperation(operation, left, right);
        }
    }
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
        case TokenTypes::CHAR_LITERAL:
        {
            unsigned char value = expression.literal.getLexeme().value()[0];
            return {Primitive::CHAR, value};
        }
        case TokenTypes::TRUE:
        {
            return {Primitive::BOOL, true};
        }
        case TokenTypes::FALSE:
        {
            return {Primitive::BOOL, false};
        }
        default: break;
    }
    // TODO: Add better error handling
    Logger::error("KryptonRuntime::evaluate - unknown literal type");
    exit(1);
}

void KryptonRuntime::execute(const Statement& statement)
{
    if (auto scopeStmt = dynamic_cast<const ScopeStatement*>(&statement))
    {
        execute(*scopeStmt);
    }
    else if (auto printStmt = dynamic_cast<const PrintStatement*>(&statement))
    {
        execute(*printStmt);
    }
    else if (auto ifStmt = dynamic_cast<const IfStatement*>(&statement))
    {
        execute(*ifStmt);
    }
    else
    {
        Logger::error("KryptonRuntime::execute - unknown statement type");
        exit(1);
    }
}

void KryptonRuntime::execute(const PrintStatement& statement)
{
    Value value = evaluate(*statement.expression);
    if (&value.getType() == &Primitive::INT)
    {
        string s = std::to_string(value.getValue<int>());
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else if (&value.getType() == &Primitive::DEC)
    {
        string s = std::to_string(value.getValue<double>());
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else if (&value.getType() == &Primitive::BOOL)
    {
        string s = value.getValue<bool>() ? "true" : "false";
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else if (&value.getType() == &Primitive::CHAR)
    {
        string s(1, value.getValue<unsigned char>());
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else
    {
        Logger::error("KryptonRuntime::execute - unknown value type");
        exit(1);
    }
}

void KryptonRuntime::execute(const ScopeStatement& statement)
{
    for (const auto& stmt : statement.statements)
    {
        execute(*stmt);
    }
}

void KryptonRuntime::execute(const IfStatement& statement)
{
    Value condition = evaluate(*statement.condition);
    if (&condition.getType() != &Primitive::BOOL)
    {
        Logger::error("KryptonRuntime::execute - if statement condition must be a boolean");
        exit(1);
    }
    if (condition.getValue<bool>())
    {
        execute(*statement.thenBranch);
    }
    else if (statement.elseBranch.has_value())
    {
        execute(*statement.elseBranch.value());
    }
}

