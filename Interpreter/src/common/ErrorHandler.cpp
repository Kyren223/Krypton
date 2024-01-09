// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/ErrorHandler.h>
#include <common/Logger.h>
#include <format>
#include <common/StringHelper.h>

ErrorHandler& ErrorHandler::getInstance()
{
    static ErrorHandler instance;
    return instance;
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

void ErrorHandler::unterminatedString(const SourceLocation& loc, const string& line, const string& problem)
{
    size_t length = StringHelper::getUtf8CharLength(problem);
    SourceLocation location = loc;
    location.column -= (int) length - 1;
    printErrorLine(location, "Unterminated string", problem,
                   line, length);
}

void ErrorHandler::unterminatedChar(const SourceLocation& loc, const string& line, const string& problem)
{
    size_t length = StringHelper::getUtf8CharLength(problem);
    SourceLocation location = loc;
    location.column -= (int) length - 1;
    printErrorLine(location, "Unterminated char", problem,
                   line, length);
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

void ErrorHandler::multiCharacterChar(const SourceLocation& loc, const string& line, const string& problem)
{
    size_t length = StringHelper::getUtf8CharLength(problem);
    SourceLocation location = loc;
    location.column -= (int) length;
    printErrorLine(location, "Multi-Character char", problem,
                   line, length);
}

void ErrorHandler::invalidEscapeSequence(const SourceLocation& loc, const string& line, size_t offset, size_t length)
{
    SourceLocation location = loc;
    location.column -= (int) (offset + 1);
    string problem = line.substr(location.column - 1, length);
    printErrorLine(location, "Invalid escape sequence", problem,
                   line, length);

}

void ErrorHandler::expectedXgotY(const SourceLocation& loc, const string& expected, const string& got)
{
    printErrorLocation(loc);
    Logger::print(LogMode::ERROR_LOG, "Expected '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, expected, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' got '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, got, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::unterminatedStatement(const SourceLocation& loc, const string& got)
{
    printErrorLocation(loc);
    Logger::print(LogMode::ERROR_LOG, "Unterminated statement, expected '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, ";", Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' got '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, got, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n\n", Color::RED);
    _hasErrors = true;
}



