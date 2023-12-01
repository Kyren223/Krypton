// Copyright (c) 2023 Krypton. All rights reserved.
#include <iostream>

/*
 * =================================================================================
 * MAJOR VERSION - Incremented when substantial new features/reworks have been done
 * MINOR VERSION - Incremented for small features/issues that have been changed
 * PATCH VERSION - Incremented only for small hotfixes/bugfixes (same functionality)
 * STABLE - A version is considered stable if it has passed all the tests
 * =================================================================================
 */

#define APPLICATION_NAME "KryptonInterpreter"
#define VERSION "0.1.1" // major.minor.patch
#define STABLE false

#if STABLE
#define STABLE_STRING "Stable"
#else
#define STABLE_STRING "Unstable"
#endif

#if DEBUG
#define DEBUG_STRING "Debug"
#else
#define DEBUG_STRING "Release"
#endif

#define BUILD_STRING "v" VERSION " (" STABLE_STRING " " DEBUG_STRING ")"


int main(const int argc, const char* argv[])
{
    std::cout << APPLICATION_NAME << " " << BUILD_STRING << std::endl;
    return 0;
}
