// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <vector>

using std::vector, std::string;

struct SourceLocation
{
    string filepath;
    int line;
    int column;
};

class ErrorHandler
{
    bool _hasErrors;
    
    ErrorHandler() : _hasErrors(false) {}
public:
    static ErrorHandler& getInstance();
    
    [[nodiscard]] bool hasErrors() const;
    void terminateIfErrors() const;
    
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
    
    // Runtime Errors Factory methods
    
private:
    void printErrorLocation(const SourceLocation& loc);
    void printErrorLine(const SourceLocation& loc, const string& error, const string& problem, const string& line, size_t problemLength);
    
};
