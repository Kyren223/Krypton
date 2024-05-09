// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <format>
using std::string;

namespace Constants
{
    
    // Interpreter
    constexpr const char* LANGUAGE = "Krypton";
    constexpr const char* INTERPRETER = "KryptonInterpreter";
    constexpr int MAJOR_VERSION = 1;
    constexpr int MINOR_VERSION = 0;
    constexpr int PATCH_VERSION = 0;
    constexpr const char* DESCRIPTION = "Expressions, Types and Statements";
    
    /*
     * =================================================================================
     * MAJOR VERSION - New language features, Breaking changes, etc.
     * MINOR VERSION - Small features, Improvements, Fixes, etc.
     * PATCH VERSION - Bug Fixes, Refactors, Optimizations, etc.
     * DESCRIPTION - Short description of the major version
     * =================================================================================
     */
    
    // Methods
    string getLanguageVersion()
    {
        return std::format("{} {} - {}",
                           LANGUAGE,
                           MAJOR_VERSION,
                           DESCRIPTION);
    }
    
    string getInterpreterVersion()
    {
        return std::format("{} {}.{}{}",
                               INTERPRETER,
                               MAJOR_VERSION,
                               MINOR_VERSION,
                               PATCH_VERSION ? std::format(".{}", PATCH_VERSION) : "",
                               DEBUG ? "d" : "");
    }
}
