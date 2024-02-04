// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Lexer.h>
#include <common/Logger.h>
#include <common/utf8/unchecked.h>
#include <common/StringHelper.h>

#include <utility>

const unordered_map<string, TokenTypes> Lexer::KEYWORDS =
        {
                {"class",    TokenTypes::CLASS},
                {"is",       TokenTypes::IS},
                {"if",       TokenTypes::IF},
                {"else",     TokenTypes::ELSE},
                {"for",      TokenTypes::FOR},
                {"while",    TokenTypes::WHILE},
                {"true",     TokenTypes::TRUE},
                {"false",    TokenTypes::FALSE},
                {"super",    TokenTypes::SUPER},
                {"this",     TokenTypes::THIS},
                {"return",   TokenTypes::RETURN},
                {"break",    TokenTypes::BREAK},
                {"continue", TokenTypes::CONTINUE},
                {"null",     TokenTypes::NUL},
                {"import",   TokenTypes::IMPORT},
                {"as",       TokenTypes::AS},
                {"from",     TokenTypes::FROM},
                {"switch",   TokenTypes::SWITCH},
                {"case",     TokenTypes::CASE},
                {"default",  TokenTypes::DEFAULT},
                {"enum",     TokenTypes::ENUM},
                {"export",   TokenTypes::EXPORT},
                {"or",       TokenTypes::OR},
                {"and",      TokenTypes::AND},
                {"print",      TokenTypes::PRINT}, // TODO: Remove this
                {"input",      TokenTypes::INPUT}, // TODO: Remove this
                
                {"void",     TokenTypes::VOID},
                {"int",      TokenTypes::INT},
                {"bool",     TokenTypes::BOOL},
                {"char",     TokenTypes::CHAR},
                {"int",      TokenTypes::INT},
                {"dec",      TokenTypes::DEC},
                {"str",      TokenTypes::STR},
                {"func",      TokenTypes::FUNC},
        };

Lexer::Lexer(const string& filepath, string source) :
    _handler(ErrorHandler::getInstance()),
    _source(std::move(source)),
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
    
    addToken(TokenTypes::END);
    _handler.terminateIfErrors();
    return _tokens;
}

bool Lexer::isAtEnd()
{
    return _current >= _source.length();
}

char Lexer::consume()
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

void Lexer::addToken(TokenTypes type)
{
    _tokens.emplace_back(_loc, type);
}

void Lexer::addToken(TokenTypes type, const string& lexeme)
{
    _tokens.emplace_back(_loc, type, lexeme);
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
    char c = consume();
    
    switch(c)
    {
        // Single-character tokens
        case '(': addToken(TokenTypes::LEFT_PAREN); break;
        case ')': addToken(TokenTypes::RIGHT_PAREN); break;
        case '{': addToken(TokenTypes::LEFT_BRACE); break;
        case '}': addToken(TokenTypes::RIGHT_BRACE); break;
        case '[': addToken(TokenTypes::LEFT_BRACKET); break;
        case ']': addToken(TokenTypes::RIGHT_BRACKET); break;
        case ',': addToken(TokenTypes::COMMA); break;
        case ':': addToken(TokenTypes::COLON); break;
        case ';': addToken(TokenTypes::SEMICOLON); break;
        case '?': addToken(TokenTypes::QUESTION_MARK); break;
        case '.': addToken(TokenTypes::DOT); break;
        case '\\': addToken(TokenTypes::BACK_SLASH); break;
        case '@': addToken(TokenTypes::AT); break;
        case '$': addToken(TokenTypes::DOLLAR); break;
        case '#': addToken(TokenTypes::HASHTAG); break;
        
        // Two-character tokens
        case '!':
            addToken(match('=') ? TokenTypes::BANG_EQUAL : TokenTypes::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenTypes::EQUAL_EQUAL : TokenTypes::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenTypes::LESS_EQUAL : TokenTypes::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenTypes::GREATER_EQUAL : TokenTypes::GREATER);
            break;
        case '*':
            addToken(match('=') ? TokenTypes::ASTERISK_EQUAL : TokenTypes::ASTERISK);
            break;
        case '%':
            addToken(match('=') ? TokenTypes::PERCENTAGE_EQUAL : TokenTypes::PERCENT);
            break;
        case '^':
            addToken(match('=') ? TokenTypes::CARET_EQUAL : TokenTypes::CARET);
            break;
        case '|':
            addToken(match('=') ? TokenTypes::PIPE_EQUAL :
                     match('|') ? TokenTypes::PIPE_PIPE : TokenTypes::PIPE);
            break;
        case '&':
            addToken(match('=') ? TokenTypes::AMPERSAND_EQUAL :
                     match('&') ? TokenTypes::AMPERSAND_AMPERSAND : TokenTypes::AMPERSAND);
            break;
        case '+':
            addToken(match('=') ? TokenTypes::PLUS_EQUAL :
                     match('+') ? TokenTypes::PLUS_PLUS : TokenTypes::PLUS);
            break;
        case '-':
            addToken(match('=') ? TokenTypes::MINUS_EQUAL :
                     (match('-') ? TokenTypes::MINUS_MINUS : TokenTypes::MINUS));
            break;
        case '/':
            if (match('/')) scanComment();
            else if (match('*')) scanMultilineComment();
            else if (match('=')) addToken(TokenTypes::SLASH_EQUAL);
            else addToken(TokenTypes::SLASH);
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
            else if (isIdentifierStart(c)) scanIdentifier();
            else _handler.unexpectedCharacter(_loc, _source);
            break;
        }
    }
}

bool Lexer::match(char expected)
{
    if (isAtEnd()) return false;
    if (peek() != expected) return false;
    
    consume();
    return true;
}

void Lexer::scanComment()
{
    _allowUtf8 = true;
    while (peek() != '\n' && !isAtEnd()) consume();
    _allowUtf8 = true;
}

void Lexer::scanMultilineComment()
{
    _allowUtf8 = true;
    while (peek() != '*' && peekNext() != '/' && !isAtEnd()) consume();
    _allowUtf8 = true;
}

void Lexer::scanString()
{
    _allowUtf8 = true;
    while (peek() != '"' && peek() != '\n' && !isAtEnd()) consume();
    _allowUtf8 = false;
    
    if (peek() != '"')
    {
        string problem = _source.substr(_start, _current - _start);
        _handler.unterminatedString(_loc, _currentLine, problem);
        consume(); // Avoid infinite loop
        return;
    }
    
    consume(); // Consume the closing "
    
    string value = _source.substr(_start + 1, _current - _start - 2);
    value = unescape(value);
    addToken(TokenTypes::STRING_LITERAL, value);
}

void Lexer::scanChar()
{
    _allowUtf8 = true;
    while (peek() != '\'' && peek() != '\n' && !isAtEnd()) consume();
    _allowUtf8 = false;
    
    if (peek() != '\'')
    {
        string problem = _source.substr(_start, _current - _start);
        _handler.unterminatedChar(_loc, _currentLine, problem);
        consume(); // Avoid infinite loop
        return;
    }
    
    consume(); // Consume the closing '
    
    string value = _source.substr(_start + 1, _current - _start - 2);
    value = unescape(value);
    if (value.length() > 1)
    {
        _handler.multiCharacterChar(_loc, _currentLine, value);
        return;
    }
    addToken(TokenTypes::CHAR_LITERAL, value);
}

void Lexer::scanNumber()
{
    if (peek() == '0')
    {
        // TODO Binary, Octal, Hexadecimal (0b, 0o, 0x)
    }
    
    while (isDigit(peek())) consume();
    
    // Look for a decimal point
    bool hasDecimal = false;
    if (peek() == '.' && isDigit(peekNext())) {
        consume(); // Consume the "."
        hasDecimal = true;
        while (isDigit(peek())) consume();
    }
    
    string value = _source.substr(_start, _current - _start);
    TokenTypes type = hasDecimal ? TokenTypes::DEC_LITERAL : TokenTypes::INT_LITERAL;
    addToken(type, value);
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

int Lexer::getBin(char c)
{
    if (c == '0') return 0;
    if (c == '1') return 1;
    return -1;
}

bool Lexer::isIdentifier(char c)
{
    return isIdentifierStart(c) || isDigit(c);
}

bool Lexer::isIdentifierStart(char c)
{
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           c == '_';
}

void Lexer::scanIdentifier()
{
    while (isIdentifier(peek())) consume();
    string value = _source.substr(_start, _current - _start);
    TokenTypes type = KEYWORDS.contains(value) ? KEYWORDS.at(value) : TokenTypes::IDENTIFIER;
    if (type == TokenTypes::IDENTIFIER) addToken(type, value);
    else addToken(type);
}


