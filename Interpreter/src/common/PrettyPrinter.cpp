// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/PrettyPrinter.h>
#include <common/Logger.h>

#define LOG(x) Logger::print(LogMode::NONE, x, Color::WHITE)

void PrettyPrinter::print(const ASTNode& node)
{
    if (const Expression* expr = dynamic_cast<const Expression*>(&node)) print(*expr);
    else LOG("Unknown node type");
}

void PrettyPrinter::print(const Expression& expr)
{
    LOG("(");
    if (const BinaryExpression* binExpr = dynamic_cast<const BinaryExpression*>(&expr))
    {
        print(*binExpr);
    }
    else if (const UnaryExpression* unExpr = dynamic_cast<const UnaryExpression*>(&expr))
    {
        print(*unExpr);
    }
    else if (const LiteralExpression* litExpr = dynamic_cast<const LiteralExpression*>(&expr))
    {
        print(*litExpr);
    }
    else LOG("Unknown expression type");
    LOG(")\n");
}

void PrettyPrinter::print(const BinaryExpression& expr)
{
    if (expr.op.getType() == TokenType::END)
    {
        LOG("END");
        return;
    }
    LOG(Token::getTokenTypeString(expr.op.getType()));
    LOG("(");
    print(*expr.left);
    print(*expr.right);
    LOG(")");
}

void PrettyPrinter::print(const UnaryExpression& expr)
{
    LOG("(");
    if (expr.op.getType() == TokenType::END)
    {
        LOG("END");
        return;
    }
    LOG(Token::getTokenTypeString(expr.op.getType()));
    print(*expr.expression);
    LOG(")");
}

void PrettyPrinter::print(const LiteralExpression& expr)
{
    optional<string> value = expr.literal.getLexeme();
    if (value.has_value()) LOG(value.value());
    else LOG(Token::getTokenTypeString(expr.literal.getType()));
}

void PrettyPrinter::printTokens(const vector<Token>& tokens)
{
    LOG("{");
    for (const Token& token : tokens)
    {
        LOG(Token::getTokenTypeString(token.getType()));
        optional<string> lexeme = token.getLexeme();
        if (lexeme.has_value()) LOG(": " + lexeme.value());
        LOG(", ");
    }
    LOG("}\n");
}
