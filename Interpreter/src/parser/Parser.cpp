// Copyright (c) 2023 Krypton. All rights reserved.
#include <parser/Parser.h>
#include <exception>
#include <utility>
#include <common/Logger.h>
#include <types/Primitive.h>

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
    vector<unique_ptr<Statement>> statements;
    while (true)
    {
        if (peek().getType() == TokenTypes::END) break;
        try { statements.push_back(std::move(parseStatement())); }
        catch (const std::exception& ignored) {}
    }
    _handler.terminateIfErrors();
    return make_unique<CodeBlock>(std::move(statements), false);
}

unique_ptr<Expression> Parser::parseExpression(int minPrecedence)
{
    Token token = peek();
    if (token.getType() == TokenTypes::END) throw std::exception();
    
    unique_ptr<Expression> left;
    
    optional<pair<int, int>> prefixPrecedence = getPrefixPrecedence(token.getType());

    // Literal Expression
    if (match(TokenTypes::INT_LITERAL,
              TokenTypes::DEC_LITERAL,
              TokenTypes::STRING_LITERAL,
              TokenTypes::CHAR_LITERAL,
              TokenTypes::IDENTIFIER,
              TokenTypes::TRUE,
              TokenTypes::FALSE,
              TokenTypes::NUL))
    {
        left = make_unique<LiteralExpression>(token);
    }
    
    // Grouped Expression
    else if (match(TokenTypes::LEFT_PAREN))
    {
        left = parseExpression();
        if (!match(TokenTypes::RIGHT_PAREN))
        {
            _handler.expectedXgotY(token.getLocation(),
                                   ")",
                                   token.toString());
            throw std::exception();
        }
    }
    
    // Input expression
    else if (match(TokenTypes::INPUT))
    {
        left = make_unique<InputExpression>();
    }
    
    // Unary Expression (operator on the left)
    else if (prefixPrecedence.has_value())
    {
        consume(); // Consume the operator
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
        if (token.getType() == TokenTypes::END) break;

        optional<pair<int, int>> postfixPrecedence = getPostfixPrecedence(token.getType());
        optional<pair<int, int>> infixPrecedence = getInfixPrecedence(token.getType());
        
        // Unary Expression (operator on the right)
        if (postfixPrecedence)
        {
            if (postfixPrecedence->first < minPrecedence) break;
            consume(); // Consume the operator

            if (token.getType() == TokenTypes::LEFT_BRACKET)
            {
                unique_ptr<Expression> right = parseExpression();
                if (consume().getType() != TokenTypes::RIGHT_BRACKET)
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

            if (token.getType() == TokenTypes::QUESTION_MARK)
            {
                unique_ptr<Expression> middle = parseExpression();
                if (consume().getType() != TokenTypes::COLON)
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
    if (token.getType() != TokenTypes::END) _current++;
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

optional<pair<int, int>> Parser::getInfixPrecedence(TokenTypes op)
{
    switch (op)
    {
        case TokenTypes::DOT: return {{1, 2}};
        
        case TokenTypes::PIPE: return {{1, 2}};
        case TokenTypes::AMPERSAND: return {{1, 2}};
        case TokenTypes::PERCENT: return {{1, 2}};
        case TokenTypes::CARET: return {{1, 2}};
        
        case TokenTypes::SLASH:
        case TokenTypes::ASTERISK:
            return {{50, 60}};
        
        case TokenTypes::PLUS:
        case TokenTypes::MINUS:
            return {{20, 30}};
        
        case TokenTypes::GREATER:
        case TokenTypes::LESS:
        case TokenTypes::BANG_EQUAL:
        case TokenTypes::EQUAL_EQUAL:
        case TokenTypes::GREATER_EQUAL:
        case TokenTypes::LESS_EQUAL:
            return {{1, 2}};
            
        case TokenTypes::OR:
        case TokenTypes::PIPE_PIPE:
            return {{1, 2}};
            
        case TokenTypes::AND:
        case TokenTypes::AMPERSAND_AMPERSAND:
            return {{1, 2}};
        default: return {};
    }
}

optional<pair<int, int>> Parser::getPrefixPrecedence(TokenTypes op)
{
    switch (op)
    {
        case TokenTypes::AT: return {{{}, 2}};
        case TokenTypes::DOLLAR: return {{{}, 2}};
        case TokenTypes::BANG: return {{{}, 2}};
        case TokenTypes::MINUS: return {{{}, 100}};
        default: return {};
    }
}

optional<pair<int, int>> Parser::getPostfixPrecedence(TokenTypes op)
{
    switch (op)
    {
        case TokenTypes::PLUS_PLUS:
        case TokenTypes::MINUS_MINUS:
            return {{1, {}}};
        default: return {};
    }
}

unique_ptr<Statement> Parser::parseStatement()
{
    Token token = peek();
    if (token.getType() == TokenTypes::END) throw std::exception();
    
    unique_ptr<Statement> statement = parseNonInlineStatement();
    if (statement == nullptr) statement = parseInlineStatement();
    
    if (statement == nullptr)
    {
        _handler.expectedXgotY(token.getLocation(),
                               "Statement",
                               token.toString());
        throw std::exception();
    }
    
    return statement;
}

unique_ptr<InlineStatement> Parser::parseInlineStatement()
{
    Token token = peek();
    if (token.getType() == TokenTypes::END) throw std::exception();
    
    // Scope Statement (Code Block)
    if (match(TokenTypes::LEFT_BRACE))
    {
        vector<unique_ptr<Statement>> statements;
        while (!match(TokenTypes::RIGHT_BRACE))
        {
            statements.push_back(std::move(parseStatement()));
        }
        return make_unique<CodeBlock>(std::move(statements));
    }
    
    // Print Statement
    else if (match(TokenTypes::PRINT))
    {
        unique_ptr<Expression> expression = parseExpression();
        token = peek();
        if (!match(TokenTypes::SEMICOLON))
        {
            _handler.unterminatedStatement(token.getLocation(), token.toString());
            throw std::exception();
        }
        return make_unique<PrintStatement>(std::move(expression));
    }
    
    // Check if the statement isn't an inline statement
    if (parseNonInlineStatement() != nullptr)
    {
        _handler.nonInlineStatementFound(token.getLocation());
    }
    else
    {
        _handler.expectedXgotY(token.getLocation(),
                               "Statement",
                               token.toString());
    }
    
    throw std::exception();
}

unique_ptr<Statement> Parser::parseNonInlineStatement()
{
    Token token = peek();
    if (token.getType() == TokenTypes::END) throw std::exception();
    
    // If Statement
    if (match(TokenTypes::IF))
    {
        token = peek();
        if (!match(TokenTypes::LEFT_PAREN))
        {
            _handler.expectedXgotY(token.getLocation(),
                                   "(",
                                   token.toString());
            throw std::exception();
        }
        unique_ptr<Expression> condition = parseExpression();
        token = peek();
        if (!match(TokenTypes::RIGHT_PAREN))
        {
            _handler.expectedXgotY(token.getLocation(),
                                   ")",
                                   token.toString());
            throw std::exception();
        }
        
        unique_ptr<InlineStatement> thenBranch = parseInlineStatement();
        
        if (match(TokenTypes::ELSE))
        {
            unique_ptr<InlineStatement> elseBranch = parseInlineStatement();
            return make_unique<IfStatement>(std::move(condition),
                                            std::move(thenBranch),
                                            std::move(elseBranch));
        }
        
        return make_unique<IfStatement>(std::move(condition),
                                        std::move(thenBranch));
    }
    
    // While Statement
    if (match(TokenTypes::WHILE))
    {
        token = peek();
        if (!match(TokenTypes::LEFT_PAREN))
        {
            _handler.expectedXgotY(token.getLocation(),
                                   "(",
                                   token.toString());
            throw std::exception();
        }
        unique_ptr<Expression> condition = parseExpression();
        token = peek();
        if (!match(TokenTypes::RIGHT_PAREN))
        {
            _handler.expectedXgotY(token.getLocation(),
                                   ")",
                                   token.toString());
            throw std::exception();
        }
        
        unique_ptr<InlineStatement> body = parseInlineStatement();
        
        return make_unique<WhileStatement>(std::move(condition),
                                           std::move(body));
    }
    
    // Variable
    unique_ptr<Statement> variableDeclaration = parseVariableDeclaration();
    if (variableDeclaration != nullptr) return variableDeclaration;
    
    return nullptr;
}

unique_ptr<Statement> Parser::parseVariableDeclaration()
{
    const Type* type;
    if (match(TokenTypes::INT)) type = &Primitive::INT;
    else if (match(TokenTypes::DEC)) type = &Primitive::DEC;
    else if (match(TokenTypes::BOOL)) type = &Primitive::BOOL;
    else if (match(TokenTypes::CHAR)) type = &Primitive::CHAR;
    else if (match(TokenTypes::STR)) type = &Primitive::STR;
    else if (peek().getType() == TokenTypes::IDENTIFIER) return parseVariableAssignment();
    else return nullptr;
    
    Token identifier = consume();
    if (identifier.getType() != TokenTypes::IDENTIFIER)
    {
        _handler.expectedXgotY(identifier.getLocation(),
                               "Identifier",
                               identifier.toString());
        throw std::exception();
    }
    
    if (!match(TokenTypes::EQUAL))
    {
        _handler.expectedXgotY(peek().getLocation(),
                               "=",
                               peek().toString());
        throw std::exception();
    }
    
    if (match(TokenTypes::SEMICOLON))
    {
        return make_unique<VariableDeclaration>(*type, std::move(identifier));
    }
    
    unique_ptr<Expression> initializer = parseExpression();
    
    if (!match(TokenTypes::SEMICOLON))
    {
        _handler.unterminatedStatement(peek().getLocation(),
                                       peek().toString());
        throw std::exception();
    }
    
    return make_unique<VariableDeclaration>(*type, std::move(identifier), std::move(initializer));
}

unique_ptr<Statement> Parser::parseVariableAssignment()
{
    Token identifier = consume();
    
    if (!match(TokenTypes::EQUAL))
    {
        _handler.expectedXgotY(peek().getLocation(),
                               "=",
                               peek().toString());
        throw std::exception();
    }
    
    unique_ptr<Expression> value = parseExpression();
    
    if (!match(TokenTypes::SEMICOLON))
    {
        _handler.unterminatedStatement(peek().getLocation(),
                                       peek().toString());
        throw std::exception();
    }
    
    return make_unique<VariableAssignment>(std::move(identifier), std::move(value));
}

template<std::same_as<TokenTypes>... Ts>
bool Parser::match(TokenTypes first, Ts... rest)
{
    if (peek().getType() == first)
    {
        consume();
        return true;
    }
    if constexpr (sizeof...(rest) > 0) return match(rest...);
    return false;
}

