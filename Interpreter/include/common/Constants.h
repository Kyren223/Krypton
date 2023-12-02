// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <string>

namespace Constants
{
    
    // Interpreter
    constexpr const char* APP_NAME = "KryptonInterpreter";
    constexpr const char* VERSION = "0.3.1";
    constexpr bool STABLE = false;
    
    /*
     * =================================================================================
     * MAJOR VERSION - Incremented when substantial new features/reworks have been done
     * MINOR VERSION - Incremented for small features/issues that have been changed
     * PATCH VERSION - Incremented only for small hotfixes/bugfixes (same functionality)
     * STABLE - A version is considered stable if it has passed all the tests
     * =================================================================================
     */
    
    // Language
    constexpr const char* LANGUAGE_NAME = "Krypton";
    constexpr int LANGUAGE_VERSION = 1;
}
