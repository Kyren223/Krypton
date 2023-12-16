// Copyright (c) 2023 Krypton. All rights reserved.
#include <parser/Parser.h>

using std::make_unique;

Parser::Parser(vector<Token> tokens)
    : _handler(ErrorHandler::getInstance())
{
    _tokens = tokens;
    _current = 0;
}

unique_ptr<ASTNode> Parser::parse()
{
    unique_ptr<ASTNode> ast = parseExpression();
    _handler.terminateIfErrors();
    return ast;
}

unique_ptr<Expression> Parser::parseExpression(int minPrecedence)
{
    Token token = peek();
    unique_ptr<Expression> left;
    
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
        left = make_unique<LiteralExpression>(token);
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
        left = make_unique<UnaryExpression>(token, std::move(left));
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
                unique_ptr<Expression> right = parseExpression();
                if (advance().getType() != TokenType::RIGHT_BRACKET)
                {
                    // TODO Error - Expected ']'
                    return nullptr;
                }
                left = make_unique<BinaryExpression>(std::move(left), token, std::move(right));
            }
            else left = make_unique<UnaryExpression>(token, std::move(left));
        }
        
        optional<pair<int, int>> infixPrecedence = getInfixPrecedence(token.getType());
        if (infixPrecedence)
        {
            if (infixPrecedence->first < minPrecedence) break;
            advance(); // Consume the operator
            
            if (token.getType() == TokenType::QUESTION_MARK)
            {
                unique_ptr<Expression> middle = parseExpression();
                if (advance().getType() != TokenType::COLON)
                {
                    // TODO Error - Expected ':'
                    return nullptr;
                }
                unique_ptr<Expression> right = parseExpression(infixPrecedence->second);
                left = make_unique<TernaryExpression>(std::move(left), std::move(middle), std::move(right));
            }
            else
            {
                unique_ptr<Expression> right = parseExpression(infixPrecedence->second);
                left = make_unique<BinaryExpression>(std::move(left), token, std::move(right));
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
        case TokenType::DOT: return {{1, 2}};
        
        case TokenType::PIPE: return {{1, 2}};
        case TokenType::AMPERSAND: return {{1, 2}};
        case TokenType::PERCENTAGE: return {{1, 2}};
        case TokenType::CARET: return {{1, 2}};
        
        case TokenType::SLASH:
        case TokenType::ASTERISK:
            return {{1, 2}};
        
        case TokenType::PLUS:
        case TokenType::MINUS:
            return {{1, 2}};
        
        case TokenType::GREATER:
        case TokenType::LESS:
        case TokenType::BANG_EQUAL:
        case TokenType::EQUAL_EQUAL:
        case TokenType::GREATER_EQUAL:
        case TokenType::LESS_EQUAL:
            return {{1, 2}};
            
        case TokenType::OR:
        case TokenType::PIPE_PIPE:
            return {{1, 2}};
            
        case TokenType::AND:
        case TokenType::AMPERSAND_AMPERSAND:
            return {{1, 2}};
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

