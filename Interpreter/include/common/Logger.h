// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <string>

using std::string;

enum class LogMode
{
    NONE, // White
    INFO, // Blue
    WARN, // Yellow
    ERROR_LOG, // Red
    DEBUG_LOG, // Green
};

enum class Color
{
    RED,
    GREEN,
    YELLOW,
    BLUE,
    WHITE,
};

class Logger
{
    static bool _verbose;
    static bool _suppressWarnings;
    static bool _silent;
    
public:
    static void setVerbose(bool verbose);
    static void setSuppressWarnings(bool suppressWarnings);
    static void setSilent(bool noOutput);
    
    // Quick print methods
    static void log(const string& message);
    static void debug(const string& message);
    static void info(const string& message);
    static void warn(const string& message);
    static void error(const string& message);
    
    // Advanced print methods
    static void print(LogMode mode, const string& message, Color color);
private:
};
