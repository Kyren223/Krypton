// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/Logger.h>
#include <iostream>
#include "windows.h"

bool Logger::_verbose = false;
bool Logger::_suppressWarnings = false;
bool Logger::_noOutput = false;

void Logger::setVerbose(bool verbose)
{
    _verbose = verbose;
}

void Logger::setSuppressWarnings(bool suppressWarnings)
{
    _suppressWarnings = suppressWarnings;
}

void Logger::setNoOutput(bool noOutput)
{
    _noOutput = noOutput;
}

void Logger::log(const std::string& message)
{
    print(message, LogMode::NONE);
}

void Logger::debug(const std::string& message)
{
    print(message, LogMode::DEBUG_LOG);
}

void Logger::info(const std::string& message)
{
    print(message, LogMode::INFO);
}

void Logger::warn(const std::string& message)
{
    print(message, LogMode::WARN);
}

void Logger::error(const std::string& message)
{
    print(message, LogMode::ERROR_LOG);
}

void Logger::print(const std::string& message, LogMode level)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (level)
    {
        case LogMode::NONE:
            if (_noOutput) return;
            SetConsoleTextAttribute(hConsole, 15);
            break;
        case LogMode::INFO:
            if (_noOutput || _verbose) return;
            SetConsoleTextAttribute(hConsole, 11);
            break;
        case LogMode::WARN:
            if (_noOutput || _suppressWarnings) return;
            SetConsoleTextAttribute(hConsole, 14);
            break;
        case LogMode::ERROR_LOG:
            SetConsoleTextAttribute(hConsole, 12);
            break;
        case LogMode::DEBUG_LOG:
            if (!DEBUG) return;
            SetConsoleTextAttribute(hConsole, 10);
            break;
    }
    std::cout << getLevelPrefix(level) << message << std::endl;
    SetConsoleTextAttribute(hConsole, 15);
}

std::string Logger::getLevelPrefix(LogMode level)
{
    switch (level)
    {
        case LogMode::NONE:
            return "";
        case LogMode::INFO:
            return "[INFO] ";
        case LogMode::WARN:
            return "[WARNING] ";
        case LogMode::ERROR_LOG:
            return "[ERROR] ";
        case LogMode::DEBUG_LOG:
            return "[DEBUG] ";
    }
}

