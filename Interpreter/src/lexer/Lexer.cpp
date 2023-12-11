// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Lexer.h>
#include <common/ErrorHandler.h>
#include <common/Logger.h>
#include <common/utf8/unchecked.h>

Lexer::Lexer(const string& filepath, const string& source)
{
    _source = source;
    _loc = SourceLocation(filepath, 1, 0);
    _start = 0;
    _current = 0;
    _allowUtf8 = false;
    _utf8 = 0;
}

vector<Token> Lexer::scanTokens()
{
    while (!isAtEnd())
    {
        _start = _current;
        scanToken();
    }
    
    addToken(TokenType::END);
    return _tokens;
}

bool Lexer::isAtEnd()
{
    return _current >= _source.length();
}

char Lexer::advance()
{
    if (isAtEnd()) return '\0';
    
    char c = _source.at(_current);
    
    if (_utf8 == 0)
    {
        string utf8Char = getUtf8Char();
        size_t length = utf8Char.size();
        if (length == 1)
        {
            if (c == '\n')
            {
                _loc.line++;
                _loc.column = 0;
            }
            else _loc.column++;
        }
        else
        {
            _loc.column++;
            if (_allowUtf8) _utf8 = length - 1;
            else
            {
                _current += length - 1;
                ErrorHandler::getInstance().unexpectedCharacter(
                        _loc,_source,utf8Char);
            }
        }
    }
    else _utf8--;
    
    _current++;
    return c;
}

void Lexer::addToken(TokenType type)
{
    _tokens.emplace_back(_loc, TokenType::END);
}

void Lexer::addToken(TokenType type, const string& lexeme)
{
    _tokens.emplace_back(_loc, TokenType::END, lexeme);
}

char Lexer::peek()
{
    return _source.at(_current);
}

char Lexer::peekNext()
{
    if (_current + 1 >= _source.length()) return '\0';
    return _source.at(_current + 1);
}

void Lexer::scanToken()
{
    char c = advance();
    
    switch(c)
    {
        // Single-character tokens
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case '[': addToken(TokenType::LEFT_BRACKET); break;
        case ']': addToken(TokenType::RIGHT_BRACKET); break;
        case ',': addToken(TokenType::COMMA); break;
        case ':': addToken(TokenType::COLON); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '?': addToken(TokenType::QUESTION_MARK); break;
        case '.': addToken(TokenType::DOT); break;
        case '\\': addToken(TokenType::BACK_SLASH); break;
        case '@': addToken(TokenType::AT); break;
        case '$': addToken(TokenType::DOLLAR); break;
        case '#': addToken(TokenType::HASHTAG); break;
        
        // Two-character tokens
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '*':
            addToken(match('=') ? TokenType::ASTERISK_EQUAL : TokenType::ASTERISK);
            break;
        case '%':
            addToken(match('=') ? TokenType::PERCENTAGE_EQUAL : TokenType::PERCENTAGE);
            break;
        case '^':
            addToken(match('=') ? TokenType::CARET_EQUAL : TokenType::CARET);
            break;
        case '|':
            addToken(match('=') ? TokenType::PIPE_EQUAL :
                     match('!') ? TokenType::PIPE_PIPE : TokenType::PIPE);
            break;
        case '&':
            addToken(match('=') ? TokenType::AMPERSAND_EQUAL :
                     match('&') ? TokenType::AMPERSAND_AMPERSAND : TokenType::AMPERSAND);
            break;
        case '+':
            addToken(match('=') ? TokenType::PLUS_EQUAL :
                     match('+') ? TokenType::PLUS_PLUS : TokenType::PLUS);
            break;
        case '-':
            addToken(match('=') ? TokenType::MINUS_EQUAL :
                     match('-') ? TokenType::MINUS_MINUS : TokenType::MINUS);
            break;
        case '/':
            if (match('/')) scanComment();
            else if (match('*')) scanMultilineComment();
            else if (match('=')) addToken(TokenType::SLASH_EQUAL);
            else addToken(TokenType::SLASH);
            break;
        
        // Literals
        case '"': scanString(); break;
        case '\'': scanChar(); break;
        
        // Whitespace
        case '\n':
        case ' ':
        case '\r':
        case '\t':
            break;
        
        default:
        {
            if (isDigit(c)) scanNumber();
            else ErrorHandler::getInstance().unexpectedCharacter(_loc, _source);
            break;
        }
    }
}

bool Lexer::match(char expected)
{
    if (isAtEnd()) return false;
    if (peek() != expected) return false;
    
    advance();
    return true;
}

void Lexer::scanComment()
{
    _allowUtf8 = true;
    while (peek() != '\n' && !isAtEnd()) advance();
    _allowUtf8 = true;
}

void Lexer::scanMultilineComment()
{
    _allowUtf8 = true;
    while (peek() != '*' && peekNext() != '/' && !isAtEnd()) advance();
    _allowUtf8 = true;
}

void Lexer::scanString()
{
    _allowUtf8 = true;
    while (peek() != '"' && !isAtEnd()) advance();
    _allowUtf8 = false;
    
    if (isAtEnd())
    {
        // TODO: Handle errors (unterminated string)
    }
    
    advance(); // Consume the closing "
    
    string value = _source.substr(_start + 1, _current - _start - 2);
    value = unescape(value);
    addToken(TokenType::STRING_LITERAL, value);
}

void Lexer::scanChar()
{
    _allowUtf8 = true;
    while (peek() != '\'' && !isAtEnd()) advance();
    _allowUtf8 = false;
    
    if (isAtEnd())
    {
        // TODO: Handle errors (unterminated char)
    }
    
    advance(); // Consume the closing '
    
    string value = _source.substr(_start + 1, _current - _start - 2);
    value = unescape(value);
    // TODO: Handle errors (char length > 1)
    addToken(TokenType::CHAR_LITERAL, value);
}

void Lexer::scanNumber()
{
    
}

bool Lexer::isDigit(char c)
{
    return c >= '0' && c <= '9';
}


string Lexer::unescape(const string& str)
{
    // TODO: Implement unescape
    return str;
}

string Lexer::getUtf8Char()
{
    // Get the UTF-8 codepoint at the current position
    utf8::unchecked::iterator<std::string::iterator> it(_source.begin() + _current);
    char32_t codepoint = *it;
    
    // Convert codepoint back to UTF-8 encoded string
    std::string currentChar;
    utf8::unchecked::append(codepoint, back_inserter(currentChar));
    
    return currentChar;
}

