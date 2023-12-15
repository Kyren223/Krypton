// Copyright (c) 2023 Krypton. All rights reserved.
#include <parser/Parser.h>

Parser::Parser(vector<Token> tokens)
    : _handler(ErrorHandler::getInstance())
{
    _tokens = tokens;
    _current = 0;
}

ASTNode* Parser::parse()
{
    ASTNode* ast = parseExpression();
    _handler.terminateIfErrors();
    return ast;
}

Expression* Parser::parseExpression(int minPrecedence)
{
    Token token = peek();
    Expression* left;
    
    optional<pair<int, int>> prefixPrecedence = getPrefixPrecedence(token.getType());
    
    // Literal Expression
    if (match(TokenType::INT_LITERAL,
              TokenType::DEC_LITERAL,
              TokenType::STRING_LITERAL,
              TokenType::CHAR_LITERAL,
              TokenType::IDENTIFIER,
              TokenType::TRUE,
              TokenType::FALSE,
              TokenType::NUL))
    {
        left = new LiteralExpression(token);
    }
    
    // Grouped Expression
    else if (match(TokenType::LEFT_PAREN))
    {
        left = parseExpression();
        if (!match(TokenType::RIGHT_PAREN))
        {
            // TODO Error - Expected ')'
        }
    }
    
    // Unary Expression (operator on the left)
    else if (prefixPrecedence)
    {
        left = parseExpression(prefixPrecedence->second);
        left = new UnaryExpression(token, left);
    }
    
    else
    {
        // TODO Error - Expected expression
        return nullptr;
    }
    
    // Binary Expression
    while (true)
    {
        token = peek();
        optional<pair<int, int>> postfixPrecedence = getPostfixPrecedence(token.getType());
        
        if (postfixPrecedence)
        {
            if (postfixPrecedence->first < minPrecedence) break;
            advance(); // Consume the operator
            
            if (token.getType() == TokenType::LEFT_BRACKET)
            {
                Expression* right = parseExpression();
                if (advance().getType() != TokenType::RIGHT_BRACKET)
                {
                    // TODO Error - Expected ']'
                    return nullptr;
                }
                left = new BinaryExpression(left, token, right);
            }
            else left = new UnaryExpression(token, left);
        }
        
        optional<pair<int, int>> infixPrecedence = getInfixPrecedence(token.getType());
        if (infixPrecedence)
        {
            if (infixPrecedence->first < minPrecedence) break;
            advance(); // Consume the operator
            
            if (token.getType() == TokenType::QUESTION_MARK)
            {
                Expression* middle = parseExpression();
                if (advance().getType() != TokenType::COLON)
                {
                    // TODO Error - Expected ':'
                    return nullptr;
                }
                Expression* right = parseExpression(infixPrecedence->second);
                left = new TernaryExpression(left, middle, right);
            }
            else
            {
                Expression* right = parseExpression(infixPrecedence->second);
                left = new BinaryExpression(left, token, right);
            }
        }
    }
    
    
    return left;
}

Token Parser::advance()
{
    if (_current >= _tokens.size()) return _tokens.at(_tokens.size() - 1);
    return _tokens[_current++];
}

Token Parser::peek() const
{
    if (_current >= _tokens.size()) return _tokens.at(_tokens.size() - 1);
    return _tokens[_current];
}

optional<pair<int, int>> Parser::getInfixPrecedence(TokenType op)
{
    switch (op)
    {
        case TokenType::COLON: return {{1, 2}};
        case TokenType::QUESTION_MARK: return {{1, 2}};
        case TokenType::DOT: return {{1, 2}};
        case TokenType::EQUAL: return {{1, 2}};
        case TokenType::GREATER: return {{1, 2}};
        case TokenType::LESS: return {{1, 2}};
        case TokenType::PIPE: return {{1, 2}};
        case TokenType::AMPERSAND: return {{1, 2}};
        case TokenType::PERCENTAGE: return {{1, 2}};
        case TokenType::CARET: return {{1, 2}};
        case TokenType::SLASH: return {{1, 2}};
        case TokenType::ASTERISK: return {{1, 2}};
        case TokenType::PLUS: return {{1, 2}};
        case TokenType::MINUS: return {{1, 2}};
        case TokenType::BANG_EQUAL: return {{1, 2}};
        case TokenType::EQUAL_EQUAL: return {{1, 2}};
        case TokenType::GREATER_EQUAL: return {{1, 2}};
        case TokenType::LESS_EQUAL: return {{1, 2}};
        case TokenType::PIPE_PIPE: return {{1, 2}};
        case TokenType::AMPERSAND_AMPERSAND: return {{1, 2}};
        case TokenType::AND: return {{1, 2}};
        case TokenType::OR: return {{1, 2}};
        default: return {};
    }
}

optional<pair<int, int>> Parser::getPrefixPrecedence(TokenType op)
{
    switch (op)
    {
        case TokenType::AT: return {{1, 2}};
        case TokenType::DOLLAR: return {{1, 2}};
        case TokenType::BANG: return {{1, 2}};
        case TokenType::MINUS: return {{1, 2}};
        default: return {};
    }}

optional<pair<int, int>> Parser::getPostfixPrecedence(TokenType op)
{
    switch (op)
    {
        case TokenType::COLON: return {{1, 2}};
        case TokenType::QUESTION_MARK: return {{1, 2}};
        case TokenType::BANG: return {{1, 2}};
        case TokenType::PLUS_PLUS: return {{1, 2}};
        case TokenType::MINUS_MINUS: return {{1, 2}};
        default: return {};
    }}

template<std::same_as<TokenType>... Ts>
bool Parser::match(TokenType first, Ts... rest)
{
    if (peek().getType() == first)
    {
        advance();
        return true;
    }
    if constexpr (sizeof...(rest) > 0) return match(rest...);
    return false;
}

