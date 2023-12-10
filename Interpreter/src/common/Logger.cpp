// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/Logger.h>
#include <iostream>
#include "windows.h"

bool Logger::_verbose = false;
bool Logger::_suppressWarnings = false;
bool Logger::_silent = false;

void Logger::setVerbose(bool verbose)
{
    _verbose = verbose;
}

void Logger::setSuppressWarnings(bool suppressWarnings)
{
    _suppressWarnings = suppressWarnings;
}

void Logger::setSilent(bool noOutput)
{
    _silent = noOutput;
}

void Logger::log(const string& message)
{
    print(message, LogMode::NONE);
}

void Logger::debug(const string& message)
{
    print(message, LogMode::DEBUG_LOG);
}

void Logger::info(const string& message)
{
    print(message, LogMode::INFO);
}

void Logger::warn(const string& message)
{
    print(message, LogMode::WARN);
}

void Logger::error(const string& message)
{
    print(message, LogMode::ERROR_LOG);
}

void Logger::print(const string& message, LogMode level)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (level)
    {
        case LogMode::NONE:
            if (_silent) return;
            SetConsoleTextAttribute(hConsole, 15);
            break;
        case LogMode::INFO:
            if (_silent || _verbose) return;
            SetConsoleTextAttribute(hConsole, 11);
            break;
        case LogMode::WARN:
            if (_silent || _suppressWarnings) return;
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
    std::cout << message << "\n";
    SetConsoleTextAttribute(hConsole, 15);
}

