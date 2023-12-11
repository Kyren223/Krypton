// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/ErrorHandler.h>
#include <common/Logger.h>
#include <format>

ErrorHandler* ErrorHandler::instance = nullptr;

ErrorHandler& ErrorHandler::getInstance()
{
    if (instance == nullptr) instance = new ErrorHandler();
    return *instance;
}

bool ErrorHandler::hasErrors() const
{
    return _hasErrors;
}

void ErrorHandler::terminateIfErrors() const
{
    if (hasErrors()) exit(1);
}

void ErrorHandler::unexpectedCharacter(const SourceLocation& loc, const string& line)
{
    printErrorLine(loc, line, 1, "Unexpected character");
}

void ErrorHandler::unterminatedString(const SourceLocation& loc, const string& line)
{

}

void ErrorHandler::unterminatedChar(const SourceLocation& loc, const string& line)
{

}

void ErrorHandler::printErrorLocation(const SourceLocation& loc)
{
    string location = std::format("{} [{}:{}]: ", loc.filepath, loc.line, loc.column);
    Logger::print(LogMode::ERROR_LOG, location, Color::BLUE);
    _hasErrors = true;
}

void ErrorHandler::printErrorLine(const SourceLocation& loc, const string& line, int length, const string& error)
{
    string problem = line.substr(loc.column - 1, length);
    
    printErrorLocation(loc);
    Logger::print(LogMode::ERROR_LOG, error + " '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, problem, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    string lineString = std::format("{} | {}\n", loc.line, line);
    Logger::print(LogMode::ERROR_LOG, lineString, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, string(loc.column + 3, ' '), Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, string(length, '^'), Color::RED);
    Logger::print(LogMode::ERROR_LOG, "\n\n", Color::RED);
}



