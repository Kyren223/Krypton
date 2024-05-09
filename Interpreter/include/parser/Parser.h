// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <vector>
#include <lexer/Token.h>
#include <nodes/ASTNode.h>
#include <nodes/Expressions.h>
#include <common/ErrorHandler.h>
#include <memory>
#include <nodes/Statements.h>
#include <nodes/FunctionNodes.h>

using std::vector, std::pair, std::unique_ptr;

class Parser
{
    ErrorHandler& _handler;
    vector<Token> _tokens;
    int _current;
    
public:
    explicit Parser(vector<Token> tokens);
    unique_ptr<ASTNode> parse();
    
private:
    Token consume();
    [[nodiscard]] Token peek() const;
    [[nodiscard]] Token peekNext() const;
    template<std::same_as<TokenTypes>... Ts>
    bool match(TokenTypes first, Ts... rest);
    
    unique_ptr<Expression> parseExpression(int minPrecedence = 0);
    unique_ptr<Statement> parseStatement();
    unique_ptr<InlineStatement> parseInlineStatement();
    unique_ptr<Statement> parseNonInlineStatement();
    unique_ptr<Statement> parseVariableDeclaration();
    unique_ptr<Statement> parseVariableAssignment(bool requireSemicolon = true);
    optional<optional<const Type*>> parseType();
    unique_ptr<LambdaExpression> parseLambda(optional<const Type*> returnType);
    
    static optional<pair<int, int>> getInfixPrecedence(TokenTypes op);
    static optional<pair<int, int>> getPrefixPrecedence(TokenTypes op);
    static optional<pair<int, int>> getPostfixPrecedence(TokenTypes op);
};
