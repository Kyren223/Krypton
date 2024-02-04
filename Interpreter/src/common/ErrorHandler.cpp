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
    if (!hasErrors()) return;
    if (_replMode) throw std::runtime_error("Error occurred");
    else exit(1);
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
    Logger::print(LogMode::ERROR_LOG, "\n", Color::RED);
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
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::unterminatedStatement(const SourceLocation& loc, const string& got)
{
    printErrorLocation(loc);
    Logger::print(LogMode::ERROR_LOG, "Unterminated statement, expected '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, ";", Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' got '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, got, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::setReplMode(bool replMode)
{
    _replMode = replMode;
}

bool ErrorHandler::isReplMode() const
{
    return _replMode;
}

void ErrorHandler::nonInlineStatementFound(const SourceLocation& loc)
{
    printErrorLocation(loc);
    Logger::print(LogMode::ERROR_LOG,"Non-Inline Statement cannot be used in the current context\n", Color::RED);
    Logger::print(LogMode::ERROR_LOG, "Help: Try introducing a Code Block\n", Color::BLUE);
    _hasErrors = true;
}

void ErrorHandler::undefinedVariable(const string& name)
{
    Logger::print(LogMode::ERROR_LOG, "Undefined variable '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::redefinedVariable(const string& name)
{
    Logger::print(LogMode::ERROR_LOG, "Redefined variable '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::nullReference(const string& name)
{
    Logger::print(LogMode::ERROR_LOG, "Cannot access variable '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' because it holds null\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::typeMismatch(const string& name, const Type& expected, const Type& got)
{
    Logger::print(LogMode::ERROR_LOG, "Type mismatch in variable '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "', expected type '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, expected.getName(), Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' got '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, got.getName(), Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::reset()
{
    _hasErrors = false;
}

void ErrorHandler::argumentLengthMismatch(const string& name, size_t expected, size_t got)
{
    Logger::print(LogMode::ERROR_LOG, "Argument length mismatch in function '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "', expected '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, std::to_string(expected), Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' got '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, std::to_string(got), Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::usingValueFromVoidFunction(const string& name)
{
    Logger::print(LogMode::ERROR_LOG, "Cannot use value from function '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' which returns void\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::noReturnStatementFound(const string& name)
{
    Logger::print(LogMode::ERROR_LOG, "Missing return statement in the current path of function '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}

void ErrorHandler::expectedTypeXgotVoid(const string& name, const Type& expected)
{
    Logger::print(LogMode::ERROR_LOG, "Expected type '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, expected.getName(), Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "' got void from function '", Color::RED);
    Logger::print(LogMode::ERROR_LOG, name, Color::BLUE);
    Logger::print(LogMode::ERROR_LOG, "'\n", Color::RED);
    _hasErrors = true;
}



