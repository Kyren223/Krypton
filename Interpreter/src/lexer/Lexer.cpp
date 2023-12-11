// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Lexer.h>
#include <common/Logger.h>
#include <common/utf8/unchecked.h>
#include <common/StringHelper.h>

Lexer::Lexer(const string& filepath, const string& source) :
    _handler(ErrorHandler::getInstance()),
    _source(source),
    _loc(filepath, 1, 0),
    _start(0),
    _current(0),
    _allowUtf8(false),
    _utf8(0)
{

}

vector<Token> Lexer::scanTokens()
{
    while (!isAtEnd())
    {
        _start = _current;
        scanToken();
    }
    
    addToken(TokenType::END);
    _handler.terminateIfErrors();
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
    _currentLine += c;
    
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
                _currentLine = "";
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
                _handler.unexpectedCharacter(_loc,_source,utf8Char);
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
    if (isAtEnd()) return '\0';
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
            else _handler.unexpectedCharacter(_loc, _source);
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
    while (peek() != '"' && peek() != '\n' && !isAtEnd()) advance();
    _allowUtf8 = false;
    
    if (peek() != '"')
    {
        string problem = _source.substr(_start, _current - _start);
        _handler.unterminatedString(_loc, _currentLine, problem);
        advance(); // Avoid infinite loop
        return;
    }
    
    advance(); // Consume the closing "
    
    string value = _source.substr(_start + 1, _current - _start - 2);
    value = unescape(value);
    addToken(TokenType::STRING_LITERAL, value);
}

void Lexer::scanChar()
{
    _allowUtf8 = true;
    while (peek() != '\'' && peek() != '\n' && !isAtEnd()) advance();
    _allowUtf8 = false;
    
    if (peek() != '\'')
    {
        string problem = _source.substr(_start, _current - _start);
        _handler.unterminatedChar(_loc, _currentLine, problem);
        advance(); // Avoid infinite loop
        return;
    }
    
    advance(); // Consume the closing '
    
    string value = _source.substr(_start + 1, _current - _start - 2);
    value = unescape(value);
    if (value.length() > 1)
    {
        _handler.multiCharacterChar(_loc, _currentLine, value);
        return;
    }
    addToken(TokenType::CHAR_LITERAL, value);
}

void Lexer::scanNumber()
{

}

bool Lexer::isDigit(char c)
{
    return c >= '0' && c <= '9';
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

string Lexer::unescape(const string& str)
{
    // \\ \n \r \t \x00 \000
    string result;
    bool error = false;
    for (size_t i = 0; i < str.length(); i++)
    {
        char c = str.at(i);
        if (c == '\\')
        {
            error = error || !scanEscapeSequence(str, result, i);
        }
        else result += c;
    }
    
    return error ? str : result;
}

bool Lexer::scanEscapeSequence(const string& str, string& result, size_t& i)
{
    i++;
    size_t length = 2;
    if (i < str.length())
    {
        char c = str.at(i);
        switch (c)
        {
            case '\\': result += '\\'; return true;
            case 'n': result += '\n'; return true;
            case 'r': result += '\r'; return true;
            case 't': result += '\t'; return true;
            case 'x':
            {
                length = 2;
                if (i + 1 >= str.length()) break;
                length = 3;
                int hex1 = getHex(str.at(i + 1));
                if (hex1 != -1 && i + 2 >= str.length())
                {
                    result += (char) hex1;
                    i++;
                    return true;
                }
                if (hex1 == -1 || i + 2 >= str.length()) break;
                int hex2 = getHex(str.at(i + 2));
                if (hex2 == -1)
                {
                    result += (char) hex1;
                    i++;
                    return true;
                }
                int hex = hex1 * 16 + hex2;
                result += (char) hex;
                i += 2;
                return true;
            }
            default:
            {
                int oct1 = getOct(c);
                if (oct1 == -1) break;
                length = 2;
                if (i + 1 >= str.length())
                {
                    result += (char) oct1;
                    i++;
                    return true;
                }
                int oct2 = getOct(str.at(i + 1));
                if (oct2 == -1)
                {
                    result += (char) oct1;
                    i++;
                    return true;
                }
                length = 3;
                if (i + 2 >= str.length())
                {
                    int oct = oct1 * 8 + oct2;
                    result += (char) oct;
                    i += 2;
                    return true;
                }
                int oct3 = getOct(str.at(i + 2));
                if (oct3 == -1)
                {
                    int oct = oct1 * 8 + oct2;
                    result += (char) oct;
                    i += 2;
                    return true;
                }
                int oct = oct1 * 64 + oct2 * 8 + oct3;
                result += (char) oct;
                i += 3;
                return true;
            }
        }
    }
    
    size_t offset = StringHelper::getUtf8CharLength(str) - i;
    _handler.invalidEscapeSequence(_loc, _currentLine, offset, length);
    return false;
}

int Lexer::getHex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

int Lexer::getOct(char c)
{
    if (c >= '0' && c <= '7') return c - '0';
    return -1;
}


