// Copyright (c) 2023 Krypton. All rights reserved.
#include <parser/Parser.h>
#include <exception>
#include <utility>
#include <common/Logger.h>

using std::make_unique;

Parser::Parser(vector<Token> tokens)
    : _handler(ErrorHandler::getInstance())
{
    _tokens = std::move(tokens);
    _current = 0;
}

unique_ptr<ASTNode> Parser::parse()
{
    // The method that is assigned to the AST, may throw an exception
    // But it also reports the error to the error handler so we don't need to catch it
    // Because we have _handler.terminateIfErrors() at the end of the method
    unique_ptr<ASTNode> ast = nullptr;
    try { ast = parseExpression(); }
    catch (const std::exception& ignored) {}
    _handler.terminateIfErrors();
    return ast;
}

unique_ptr<Expression> Parser::parseExpression(int minPrecedence)
{
    Token token = peek();
    if (token.getType() == TokenType::END) throw std::exception();
    
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
            _handler.expectedXgotY(token.getLocation(),
                                   ")",
                                   token.toString());
            throw std::exception();
        }
    }
    
    // Unary Expression (operator on the left)
    else if (prefixPrecedence)
    {
        left = parseExpression(prefixPrecedence->second);
        left = make_unique<UnaryExpression>(token, std::move(left));
    }
    
    // Invalid Expression
    else
    {
        _handler.expectedXgotY(token.getLocation(),
                               "Expression",
                               token.toString());
        return nullptr;
    }
    
    while (true)
    {
        token = peek();
        if (token.getType() == TokenType::END) break;

        optional<pair<int, int>> postfixPrecedence = getPostfixPrecedence(token.getType());
        optional<pair<int, int>> infixPrecedence = getInfixPrecedence(token.getType());
        
        // Unary Expression (operator on the right)
        if (postfixPrecedence)
        {
            if (postfixPrecedence->first < minPrecedence) break;
            consume(); // Consume the operator

            if (token.getType() == TokenType::LEFT_BRACKET)
            {
                unique_ptr<Expression> right = parseExpression();
                if (consume().getType() != TokenType::RIGHT_BRACKET)
                {
                    _handler.expectedXgotY(token.getLocation(),
                                           "]",
                                           token.toString());
                    throw std::exception();
                }
                left = make_unique<BinaryExpression>(std::move(left), token, std::move(right));
            }
            else left = make_unique<UnaryExpression>(token, std::move(left));
        }
        
        // Binary Expression
        else if (infixPrecedence)
        {
            if (infixPrecedence->first < minPrecedence) break;
            consume(); // Consume the operator

            if (token.getType() == TokenType::QUESTION_MARK)
            {
                unique_ptr<Expression> middle = parseExpression();
                if (consume().getType() != TokenType::COLON)
                {
                    _handler.expectedXgotY(token.getLocation(),
                                           ":",
                                           token.toString());
                    throw std::exception();
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
        
        // No more operators, exit to avoid infinite loop
        else break;
    }
    
    return left;
}

Token Parser::consume()
{
    Token token = peek();
    if (token.getType() != TokenType::END) _current++;
    if (_current >= _tokens.size())
    {
        Logger::error("Parser - Tried to consume past the end of the token stream");
        exit(1);
    }
    return token;
}

Token Parser::peek() const
{
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
        consume();
        return true;
    }
    if constexpr (sizeof...(rest) > 0) return match(rest...);
    return false;
}

