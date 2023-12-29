// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <lexer/Token.h>
#include <common/Logger.h>

struct Operation
{
    enum class Binary
    {
        PLUS,
        MINUS,
        ASTERISK,
        SLASH,
        PERCENT,
        CARET,
    };
    
    enum class Unary
    {
        MINUS,
        PLUS_PLUS,
        MINUS_MINUS,
        AT,
        BANG,
        DOLLAR,
    };
    
    [[nodiscard]] static Binary getBinaryOperation(TokenTypes op)
    {
        switch (op)
        {
//        case TokenTypes::DOT:break;

//        case TokenTypes::GREATER:break;
//        case TokenTypes::LESS:break;
//        case TokenTypes::PIPE:break;
//        case TokenTypes::AMPERSAND:break;
            case TokenTypes::PERCENT: return Binary::PERCENT;
            case TokenTypes::CARET: return Binary::CARET;
            case TokenTypes::SLASH: return Binary::SLASH;
            case TokenTypes::ASTERISK: return Binary::ASTERISK;
            case TokenTypes::PLUS: return Binary::PLUS;
            case TokenTypes::MINUS: return Binary::MINUS;

//        case TokenTypes::BANG_EQUAL:break;
//        case TokenTypes::EQUAL_EQUAL:break;
//        case TokenTypes::GREATER_EQUAL:break;
//        case TokenTypes::LESS_EQUAL:break;
//
//        case TokenTypes::PIPE_PIPE:break;
//        case TokenTypes::AMPERSAND_AMPERSAND:break;
//
//        case TokenTypes::IS:break;
//        case TokenTypes::AND:break;
//        case TokenTypes::OR:break;
            
            default: break;
        }
        // TODO: Add better error handling
        Logger::error("Operation::getBinaryOperation - unknown operation");
        exit(1);
    }
    [[nodiscard]] static Unary getUnaryOperation(TokenTypes op)
    {
        switch (op)
        {
            case TokenTypes::DOLLAR: return Unary::DOLLAR;
            case TokenTypes::AT: return Unary::AT;
            case TokenTypes::BANG: return Unary::BANG;
            case TokenTypes::MINUS: return Unary::MINUS;
            case TokenTypes::PLUS_PLUS: return Unary::PLUS_PLUS;
            case TokenTypes::MINUS_MINUS: return Unary::MINUS_MINUS;
            default: break;
        }
        
        // TODO: Add better error handling
        Logger::error("Operation::getUnaryOperation - unknown operation");
        exit(1);
    }
};