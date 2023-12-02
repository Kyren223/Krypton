// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <string>

enum class LogMode
{
    NONE, // White
    INFO, // Blue
    WARN, // Yellow
    ERROR_LOG, // Red
    DEBUG_LOG, // Green
};

class Logger
{
    static bool _verbose;
    static bool _suppressWarnings;
    static bool _silent;
    
public:
    static void setVerbose(bool verbose);
    static void setSuppressWarnings(bool suppressWarnings);
    static void setNoOutput(bool noOutput);
    
    static void log(const std::string& message);
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);
    
    static void print(const std::string& message, LogMode mode);
private:
    static std::string getLevelPrefix(LogMode mode);
};
