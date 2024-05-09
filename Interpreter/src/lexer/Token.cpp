// Copyright (c) 2023 Krypton. All rights reserved.
#include <lexer/Token.h>
#include <format>
#include <utility>

Token::Token(SourceLocation loc, TokenTypes type, string lexeme)
    : _loc(std::move(loc)), _type(type), _lexeme(lexeme)
{

}

Token::Token(SourceLocation loc, TokenTypes type)
    : _loc(std::move(loc)), _type(type)
{
    _lexeme = {};
}


SourceLocation Token::getLocation() const
{
    return _loc;
}

TokenTypes Token::getType() const
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

string Token::getTokenTypeString(TokenTypes type)
{
    switch (type)
    {
        case TokenTypes::LEFT_PAREN: return "(";
        case TokenTypes::RIGHT_PAREN: return ")";
        case TokenTypes::LEFT_BRACE: return "{";
        case TokenTypes::RIGHT_BRACE: return "}";
        case TokenTypes::LEFT_BRACKET: return "[";
        case TokenTypes::RIGHT_BRACKET: return "]";
        case TokenTypes::COMMA: return ",";
        case TokenTypes::COLON: return ":";
        case TokenTypes::SEMICOLON: return ";";
        case TokenTypes::QUESTION_MARK: return "?";
        case TokenTypes::DOT: return ".";
        case TokenTypes::BACK_SLASH: return "\\";
        case TokenTypes::AT: return "@";
        case TokenTypes::DOLLAR: return "$";
        case TokenTypes::HASHTAG: return "#";
        case TokenTypes::BANG: return "!";
        case TokenTypes::EQUAL: return "=";
        case TokenTypes::GREATER: return ">";
        case TokenTypes::LESS: return "<";
        case TokenTypes::PIPE: return "|";
        case TokenTypes::AMPERSAND: return "&";
        case TokenTypes::PERCENT: return "%";
        case TokenTypes::CARET: return "^";
        case TokenTypes::SLASH: return "/";
        case TokenTypes::ASTERISK: return "*";
        case TokenTypes::PLUS: return "+";
        case TokenTypes::MINUS: return "-";
        case TokenTypes::BANG_EQUAL: return "!=";
        case TokenTypes::EQUAL_EQUAL: return "==";
        case TokenTypes::GREATER_EQUAL: return ">=";
        case TokenTypes::LESS_EQUAL: return "<=";
        case TokenTypes::PIPE_EQUAL: return "|=";
        case TokenTypes::AMPERSAND_EQUAL: return "&=";
        case TokenTypes::PERCENTAGE_EQUAL: return "%=";
        case TokenTypes::CARET_EQUAL: return "^=";
        case TokenTypes::SLASH_EQUAL: return "/=";
        case TokenTypes::ASTERISK_EQUAL: return "*=";
        case TokenTypes::PLUS_EQUAL: return "+=";
        case TokenTypes::MINUS_EQUAL: return "-=";
        case TokenTypes::PIPE_PIPE: return "||";
        case TokenTypes::AMPERSAND_AMPERSAND: return "&&";
        case TokenTypes::PLUS_PLUS: return "++";
        case TokenTypes::MINUS_MINUS: return "--";
        case TokenTypes::IDENTIFIER: return "Identifier";
        case TokenTypes::CHAR_LITERAL: return "char";
        case TokenTypes::STRING_LITERAL: return "String";
        case TokenTypes::INT_LITERAL: return "int";
        case TokenTypes::DEC_LITERAL: return "dec";
        case TokenTypes::CLASS: return "class";
        case TokenTypes::IS: return "is";
        case TokenTypes::IF: return "if";
        case TokenTypes::ELSE: return "else";
        case TokenTypes::FOR: return "for";
        case TokenTypes::WHILE: return "while";
        case TokenTypes::TRUE: return "true";
        case TokenTypes::FALSE: return "false";
        case TokenTypes::SUPER: return "super";
        case TokenTypes::THIS: return "this";
        case TokenTypes::RETURN: return "return";
        case TokenTypes::BREAK: return "break";
        case TokenTypes::CONTINUE: return "continue";
        case TokenTypes::NUL: return "null";
        case TokenTypes::IMPORT: return "import";
        case TokenTypes::AS: return "as";
        case TokenTypes::FROM: return "from";
        case TokenTypes::SWITCH: return "switch";
        case TokenTypes::CASE: return "case";
        case TokenTypes::DEFAULT: return "default";
        case TokenTypes::ENUM: return "enum";
        case TokenTypes::EXPORT: return "export";
        case TokenTypes::AND: return "and";
        case TokenTypes::OR: return "or";
        case TokenTypes::VOID: return "void";
        case TokenTypes::BOOL: return "bool";
        case TokenTypes::CHAR: return "char";
        case TokenTypes::INT: return "int";
        case TokenTypes::DEC: return "dec";
        case TokenTypes::STR: return "str";
        case TokenTypes::END: return "EOF";
    }
}
