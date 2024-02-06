// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <vector>
#include <lexer/Token.h>
#include <common/SourceLocation.h>
#include <types/Type.h>

using std::vector, std::string;

class ErrorHandler
{
    bool _hasErrors;
    bool _replMode;
    
    ErrorHandler() : _hasErrors(false) {}
public:
    static ErrorHandler& getInstance();
    
    [[nodiscard]] bool hasErrors() const;
    void setReplMode(bool replMode);
    [[nodiscard]] bool isReplMode() const;
    void terminateIfErrors() const;
    void reset();
    
    // Command Line Errors Factory methods
    
    // Lexer Errors Factory methods
    void unexpectedCharacter(const SourceLocation& loc, const string& line);
    void unexpectedCharacter(const SourceLocation& loc, const string& line, const string& problem);
    void unterminatedString(const SourceLocation& loc, const string& line, const string& problem);
    void unterminatedChar(const SourceLocation& loc, const string& line, const string& problem);
    void multiCharacterChar(const SourceLocation& loc, const string& line, const string& problem);
    void invalidEscapeSequence(const SourceLocation& loc, const string& line, size_t offset, size_t length);
    
    // Parser Errors Factory methods
    void expectedXgotY(const SourceLocation& loc, const string& expected, const string& got);
    void unterminatedStatement(const SourceLocation& loc, const string& got);
    void nonInlineStatementFound(const SourceLocation& loc);
    
    // Runtime Errors Factory methods
    void undefinedVariable(const string& name);
    void redefinedVariable(const string& name);
    void nullReference(const string& name);
    void typeMismatch(const string& name, optional<const Type*> expected, const Type& got);
    void argumentLengthMismatch(const string& name, size_t expected, size_t got);
    void usingValueFromVoidFunction(const string& name);
    void noReturnStatementFound(const string& name);
    void expectedTypeXgotVoid(const string& name, optional<const Type*> expected);

private:
    void printErrorLocation(const SourceLocation& loc);
    void printErrorLine(const SourceLocation& loc, const string& error, const string& problem, const string& line, size_t problemLength);
    
};
