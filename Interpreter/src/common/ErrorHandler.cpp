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
    unexpectedCharacter(loc, line, line.substr(loc.column - 1, 1));
}

void ErrorHandler::unexpectedCharacter(const SourceLocation& loc, const string& line, const string& problem)
{
    printErrorLine(loc, "Unexpected character", problem, line, 1);
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

void ErrorHandler::printErrorLine(const SourceLocation& loc, const string& error, const string& problem, const string& line, size_t problemLength)
{
    printErrorLocation(loc);
    Logger::print(LogMode::ERROR_LOG, error + " '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, problem, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    string lineString = std::format("{} | {}\n", loc.line, line);
    Logger::print(LogMode::ERROR_LOG, lineString, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, string(loc.column + 3, ' '), Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, string(problemLength, '^'), Color::RED);
    Logger::print(LogMode::ERROR_LOG, "\n\n", Color::RED);
}



