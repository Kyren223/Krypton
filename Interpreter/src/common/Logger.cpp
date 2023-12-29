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
    print(LogMode::NONE, message, Color::WHITE);
}

void Logger::debug(const string& message)
{
    if (DEBUG == false) return;
    print(LogMode::DEBUG_LOG, message, Color::GREEN);
}

void Logger::info(const string& message)
{
    print(LogMode::INFO, message, Color::BLUE);
}

void Logger::warn(const string& message)
{
    print(LogMode::WARN, message, Color::YELLOW);
}

void Logger::error(const string& message)
{
    print(LogMode::ERROR_LOG, message, Color::RED);
}

void Logger::print(LogMode mode, const string& message, Color color)
{
    bool isDebug = DEBUG == true && mode == LogMode::DEBUG_LOG;
    if (mode != LogMode::ERROR_LOG && !isDebug)
    {
        if (_silent) return;
        if (mode == LogMode::WARN && _suppressWarnings) return;
        if (mode == LogMode::INFO && !_verbose) return;
    }
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    switch (color)
    {
        case Color::RED:
            SetConsoleTextAttribute(hConsole, 4);
            break;
        case Color::GREEN:
            SetConsoleTextAttribute(hConsole, 10);
            break;
        case Color::YELLOW:
            SetConsoleTextAttribute(hConsole, 14);
            break;
        case Color::BLUE:
            SetConsoleTextAttribute(hConsole, 1);
            break;
        case Color::WHITE:
            SetConsoleTextAttribute(hConsole, 15);
            break;
    }
    
    std::cout << message;
    SetConsoleTextAttribute(hConsole, 15);
}

