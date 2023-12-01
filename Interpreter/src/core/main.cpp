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
#define VERSION "0.1.0" // major.minor.patch
#define STABLE false

#define STABLE_STRING (STABLE ? "Stable" : "Unstable")
#define DEBUG_STRING (DEBUG ? "Debug" : "Release")
#define BUILD_STRING std::string("v") + VERSION + " (" + STABLE_STRING + " " + DEBUG_STRING + ")"


int main(const int argc, const char** argv)
{
    std::cout << APPLICATION_NAME << " " << BUILD_STRING << std::endl;
    return 0;
}
