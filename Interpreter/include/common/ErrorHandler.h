// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <vector>
#include <common/Error.h>

using std::vector;

class ErrorHandler
{
    static ErrorHandler* instance;
    bool _hasErrors;
    
    ErrorHandler() : _hasErrors(false) {}
public:
    static ErrorHandler& getInstance();
    
    [[nodiscard]] bool hasErrors() const;
    void terminateIfErrors() const;
    
    // Command Line Errors Factory methods
    
    // Lexer Errors Factory methods
    void unexpectedCharacter(const SourceLocation& loc, const string& line);
    void unterminatedString(const SourceLocation& loc, const string& line);
    void unterminatedChar(const SourceLocation& loc, const string& line);
    
    // Parser Errors Factory methods
    
    // Runtime Errors Factory methods
    
private:
    void printErrorLocation(const SourceLocation& loc);
    void printErrorLine(const SourceLocation& loc, const string& line, int length, const string& error);
};
