// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Token.h>
#include <format>

Token::Token(SourceLocation loc, TokenType type, string lexeme)
    : _loc(loc), _type(type), _lexeme(lexeme)
{

}

Token::Token(SourceLocation loc, TokenType type)
    : _loc(loc), _type(type)
{
    _lexeme = {};
}


SourceLocation Token::getLocation() const
{
    return _loc;
}

TokenType Token::getType() const
{
    return _type;
}

optional<string> Token::getLexeme() const
{
    return _lexeme;
}

string Token::toString()
{
    if (_lexeme) return std::format("{} ({})", _lexeme.value(), getTokenTypeString(_type));
    else return getTokenTypeString(_type);
}

string Token::getTokenTypeString(TokenType type)
{
    switch (type)
    {
        case TokenType::LEFT_PAREN: return "(";
        case TokenType::RIGHT_PAREN: return ")";
        case TokenType::LEFT_BRACE: return "{";
        case TokenType::RIGHT_BRACE: return "}";
        case TokenType::LEFT_BRACKET: return "[";
        case TokenType::RIGHT_BRACKET: return "]";
        case TokenType::COMMA: return ",";
        case TokenType::COLON: return ":";
        case TokenType::SEMICOLON: return ";";
        case TokenType::QUESTION_MARK: return "?";
        case TokenType::DOT: return ".";
        case TokenType::BACK_SLASH: return "\\";
        case TokenType::AT: return "@";
        case TokenType::DOLLAR: return "$";
        case TokenType::HASHTAG: return "#";
        case TokenType::BANG: return "!";
        case TokenType::EQUAL: return "=";
        case TokenType::GREATER: return ">";
        case TokenType::LESS: return "<";
        case TokenType::PIPE: return "|";
        case TokenType::AMPERSAND: return "&";
        case TokenType::PERCENTAGE: return "%";
        case TokenType::CARET: return "^";
        case TokenType::SLASH: return "/";
        case TokenType::ASTERISK: return "*";
        case TokenType::PLUS: return "+";
        case TokenType::MINUS: return "-";
        case TokenType::BANG_EQUAL: return "!=";
        case TokenType::EQUAL_EQUAL: return "==";
        case TokenType::GREATER_EQUAL: return ">=";
        case TokenType::LESS_EQUAL: return "<=";
        case TokenType::PIPE_EQUAL: return "|=";
        case TokenType::AMPERSAND_EQUAL: return "&=";
        case TokenType::PERCENTAGE_EQUAL: return "%=";
        case TokenType::CARET_EQUAL: return "^=";
        case TokenType::SLASH_EQUAL: return "/=";
        case TokenType::ASTERISK_EQUAL: return "*=";
        case TokenType::PLUS_EQUAL: return "+=";
        case TokenType::MINUS_EQUAL: return "-=";
        case TokenType::PIPE_PIPE: return "||";
        case TokenType::AMPERSAND_AMPERSAND: return "&&";
        case TokenType::PLUS_PLUS: return "++";
        case TokenType::MINUS_MINUS: return "--";
        case TokenType::IDENTIFIER: return "Identifier";
        case TokenType::CHAR_LITERAL: return "char";
        case TokenType::STRING_LITERAL: return "String";
        case TokenType::INT_LITERAL: return "int";
        case TokenType::DEC_LITERAL: return "dec";
        case TokenType::CLASS: return "class";
        case TokenType::IS: return "is";
        case TokenType::IF: return "if";
        case TokenType::ELSE: return "else";
        case TokenType::FOR: return "for";
        case TokenType::WHILE: return "while";
        case TokenType::TRUE: return "true";
        case TokenType::FALSE: return "false";
        case TokenType::SUPER: return "super";
        case TokenType::THIS: return "this";
        case TokenType::RETURN: return "return";
        case TokenType::BREAK: return "break";
        case TokenType::CONTINUE: return "continue";
        case TokenType::NUL: return "null";
        case TokenType::IMPORT: return "import";
        case TokenType::AS: return "as";
        case TokenType::FROM: return "from";
        case TokenType::SWITCH: return "switch";
        case TokenType::CASE: return "case";
        case TokenType::DEFAULT: return "default";
        case TokenType::ENUM: return "enum";
        case TokenType::EXPORT: return "export";
        case TokenType::AND: return "and";
        case TokenType::OR: return "or";
        case TokenType::VOID: return "void";
        case TokenType::BOOL: return "bool";
        case TokenType::CHAR: return "char";
        case TokenType::INT: return "int";
        case TokenType::DEC: return "dec";
        case TokenType::END: return "EOF";
    }
}
