// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <vector>
#include <lexer/Token.h>
#include <nodes/ASTNode.h>
#include <nodes/Expressions.h>
#include <common/ErrorHandler.h>
#include <memory>

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
    template<std::same_as<TokenType>... Ts>
    bool match(TokenType first, Ts... rest);
    
    unique_ptr<Expression> parseExpression(int minPrecedence = 0);
    
    static optional<pair<int, int>> getInfixPrecedence(TokenType op);
    static optional<pair<int, int>> getPrefixPrecedence(TokenType op);
    static optional<pair<int, int>> getPostfixPrecedence(TokenType op);
};
