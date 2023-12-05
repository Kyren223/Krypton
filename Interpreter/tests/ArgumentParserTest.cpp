// Copyright (c) 2023 Krypton. All rights reserved.
#include <catch2/catch_test_macros.hpp>
#include <cli/ArgumentParser.h>
#include <iostream>

bool areOptionsEqual(const vector<string>& options, const vector<string>& expectedOptions)
{
    if (options.size() != expectedOptions.size()) return false;
    
    for (int i = 0; i < options.size(); i++)
    {
        if (options[i] != expectedOptions[i]) return false;
    }
    
    return true;
}

#define CHECK_HAS_ARGUMENT(arg, b) REQUIRE(parser.hasArgument(Argument::arg) == b)
#define CHECK_ARGUMENT_OPTIONS(arg, options) CHECK(areOptionsEqual(parser.getArgumentOptions(Argument::arg), options))


TEST_CASE("ArgumentParser")
{
    SECTION("0 arguments")
    {
        int argc = 1;
        const char* argv[] = {};
        ArgumentParser parser(argc, argv);
        
        CHECK_HAS_ARGUMENT(PATH, false);
        CHECK_HAS_ARGUMENT(HELP, false);
        CHECK_HAS_ARGUMENT(VERSION, false);
        CHECK_HAS_ARGUMENT(BUILD, false);
        CHECK_HAS_ARGUMENT(RUN, false);
        CHECK_HAS_ARGUMENT(INCLUDE_SUBDIRECTORIES, false);
        CHECK_HAS_ARGUMENT(NO_STD, false);
        CHECK_HAS_ARGUMENT(SUPPRESS_WARNINGS, false);
        CHECK_HAS_ARGUMENT(VERBOSE, false);
        CHECK_HAS_ARGUMENT(SILENT, false);
        CHECK_HAS_ARGUMENT(COMPILE, false);
        CHECK_HAS_ARGUMENT(MODULES, false);
        CHECK_HAS_ARGUMENT(LIBS, false);
        
        CHECK_ARGUMENT_OPTIONS(PATH, {});
        CHECK_ARGUMENT_OPTIONS(HELP, {});
        CHECK_ARGUMENT_OPTIONS(VERSION, {});
        CHECK_ARGUMENT_OPTIONS(BUILD, {});
        CHECK_ARGUMENT_OPTIONS(RUN, {});
        CHECK_ARGUMENT_OPTIONS(INCLUDE_SUBDIRECTORIES, {});
        CHECK_ARGUMENT_OPTIONS(NO_STD, {});
        CHECK_ARGUMENT_OPTIONS(SUPPRESS_WARNINGS, {});
        CHECK_ARGUMENT_OPTIONS(VERBOSE, {});
        CHECK_ARGUMENT_OPTIONS(SILENT, {});
        CHECK_ARGUMENT_OPTIONS(COMPILE, {});
        CHECK_ARGUMENT_OPTIONS(MODULES, {});
        CHECK_ARGUMENT_OPTIONS(LIBS, {});
    }
    
    SECTION("1 argument")
    {
        SECTION("PATH")
        {
            int argc = 2;
            const char* argv[] = {"krypton", "path"};
            ArgumentParser parser(argc, argv);
            
            CHECK_HAS_ARGUMENT(PATH, true);
            CHECK_HAS_ARGUMENT(HELP, false);
            CHECK_HAS_ARGUMENT(VERSION, false);
            CHECK_HAS_ARGUMENT(BUILD, false);
            CHECK_HAS_ARGUMENT(RUN, false);
            CHECK_HAS_ARGUMENT(INCLUDE_SUBDIRECTORIES, false);
            CHECK_HAS_ARGUMENT(NO_STD, false);
            CHECK_HAS_ARGUMENT(SUPPRESS_WARNINGS, false);
            CHECK_HAS_ARGUMENT(VERBOSE, false);
            CHECK_HAS_ARGUMENT(SILENT, false);
            CHECK_HAS_ARGUMENT(COMPILE, false);
            CHECK_HAS_ARGUMENT(MODULES, false);
            CHECK_HAS_ARGUMENT(LIBS, false);
            
            vector<string> options = {"path"};
            CHECK_ARGUMENT_OPTIONS(PATH, options);
            CHECK_ARGUMENT_OPTIONS(HELP, {});
            CHECK_ARGUMENT_OPTIONS(VERSION, {});
            CHECK_ARGUMENT_OPTIONS(BUILD, {});
            CHECK_ARGUMENT_OPTIONS(RUN, {});
            CHECK_ARGUMENT_OPTIONS(INCLUDE_SUBDIRECTORIES, {});
            CHECK_ARGUMENT_OPTIONS(NO_STD, {});
            CHECK_ARGUMENT_OPTIONS(SUPPRESS_WARNINGS, {});
            CHECK_ARGUMENT_OPTIONS(VERBOSE, {});
            CHECK_ARGUMENT_OPTIONS(SILENT, {});
            CHECK_ARGUMENT_OPTIONS(COMPILE, {});
            CHECK_ARGUMENT_OPTIONS(MODULES, {});
            CHECK_ARGUMENT_OPTIONS(LIBS, {});
        }
        
        SECTION("HELP")
        {
            int argc = 2;
            const char* argv[] = {"krypton", "--help"};
            ArgumentParser parser(argc, argv);
            
            CHECK_HAS_ARGUMENT(PATH, false);
            CHECK_HAS_ARGUMENT(HELP, true);
            CHECK_HAS_ARGUMENT(VERSION, false);
            CHECK_HAS_ARGUMENT(BUILD, false);
            CHECK_HAS_ARGUMENT(RUN, false);
            CHECK_HAS_ARGUMENT(INCLUDE_SUBDIRECTORIES, false);
            CHECK_HAS_ARGUMENT(NO_STD, false);
            CHECK_HAS_ARGUMENT(SUPPRESS_WARNINGS, false);
            CHECK_HAS_ARGUMENT(VERBOSE, false);
            CHECK_HAS_ARGUMENT(SILENT, false);
            CHECK_HAS_ARGUMENT(COMPILE, false);
            CHECK_HAS_ARGUMENT(MODULES, false);
            CHECK_HAS_ARGUMENT(LIBS, false);
            
            CHECK_ARGUMENT_OPTIONS(PATH, {});
            CHECK_ARGUMENT_OPTIONS(HELP, {});
            CHECK_ARGUMENT_OPTIONS(VERSION, {});
            CHECK_ARGUMENT_OPTIONS(BUILD, {});
            CHECK_ARGUMENT_OPTIONS(RUN, {});
            CHECK_ARGUMENT_OPTIONS(INCLUDE_SUBDIRECTORIES, {});
            CHECK_ARGUMENT_OPTIONS(NO_STD, {});
            CHECK_ARGUMENT_OPTIONS(SUPPRESS_WARNINGS, {});
            CHECK_ARGUMENT_OPTIONS(VERBOSE, {});
            CHECK_ARGUMENT_OPTIONS(SILENT, {});
            CHECK_ARGUMENT_OPTIONS(COMPILE, {});
            CHECK_ARGUMENT_OPTIONS(MODULES, {});
            CHECK_ARGUMENT_OPTIONS(LIBS, {});
        }
    }
    
    SECTION("2 arguments")
    {
        SECTION("PATH HELP")
        {
            int argc = 3;
            const char* argv[] = {"krypton", "path", "--help"};
            ArgumentParser parser(argc, argv);
            
            CHECK_HAS_ARGUMENT(PATH, true);
            CHECK_HAS_ARGUMENT(HELP, true);
            CHECK_HAS_ARGUMENT(VERSION, false);
            CHECK_HAS_ARGUMENT(BUILD, false);
            CHECK_HAS_ARGUMENT(RUN, false);
            CHECK_HAS_ARGUMENT(INCLUDE_SUBDIRECTORIES, false);
            CHECK_HAS_ARGUMENT(NO_STD, false);
            CHECK_HAS_ARGUMENT(SUPPRESS_WARNINGS, false);
            CHECK_HAS_ARGUMENT(VERBOSE, false);
            CHECK_HAS_ARGUMENT(SILENT, false);
            CHECK_HAS_ARGUMENT(COMPILE, false);
            CHECK_HAS_ARGUMENT(MODULES, false);
            CHECK_HAS_ARGUMENT(LIBS, false);
            
            CHECK_ARGUMENT_OPTIONS(PATH, { "path" });
            CHECK_ARGUMENT_OPTIONS(HELP, {});
            CHECK_ARGUMENT_OPTIONS(VERSION, {});
            CHECK_ARGUMENT_OPTIONS(BUILD, {});
            CHECK_ARGUMENT_OPTIONS(RUN, {});
            CHECK_ARGUMENT_OPTIONS(INCLUDE_SUBDIRECTORIES, {});
            CHECK_ARGUMENT_OPTIONS(NO_STD, {});
            CHECK_ARGUMENT_OPTIONS(SUPPRESS_WARNINGS, {});
            CHECK_ARGUMENT_OPTIONS(VERBOSE, {});
            CHECK_ARGUMENT_OPTIONS(SILENT, {});
            CHECK_ARGUMENT_OPTIONS(COMPILE, {});
            CHECK_ARGUMENT_OPTIONS(MODULES, {});
            CHECK_ARGUMENT_OPTIONS(LIBS, {});
        }
        
        SECTION("PATH PATH")
        {
            int argc = 3;
            const char* argv[] = {"krypton", "path", "path"};
            ArgumentParser parser(argc, argv);
            
            CHECK_HAS_ARGUMENT(PATH, true);
            CHECK_HAS_ARGUMENT(HELP, false);
            CHECK_HAS_ARGUMENT(VERSION, false);
            CHECK_HAS_ARGUMENT(BUILD, false);
            CHECK_HAS_ARGUMENT(RUN, false);
            CHECK_HAS_ARGUMENT(INCLUDE_SUBDIRECTORIES, false);
            CHECK_HAS_ARGUMENT(NO_STD, false);
            CHECK_HAS_ARGUMENT(SUPPRESS_WARNINGS, false);
            CHECK_HAS_ARGUMENT(VERBOSE, false);
            CHECK_HAS_ARGUMENT(SILENT, false);
            CHECK_HAS_ARGUMENT(COMPILE, false);
            CHECK_HAS_ARGUMENT(MODULES, false);
            CHECK_HAS_ARGUMENT(LIBS, false);
            
            vector<string> options = {"path", "path"};
            CHECK_ARGUMENT_OPTIONS(PATH, options);
            CHECK_ARGUMENT_OPTIONS(HELP, {});
            CHECK_ARGUMENT_OPTIONS(VERSION, {});
            CHECK_ARGUMENT_OPTIONS(BUILD, {});
            CHECK_ARGUMENT_OPTIONS(RUN, {});
            CHECK_ARGUMENT_OPTIONS(INCLUDE_SUBDIRECTORIES, {});
            CHECK_ARGUMENT_OPTIONS(NO_STD, {});
            CHECK_ARGUMENT_OPTIONS(SUPPRESS_WARNINGS, {});
            CHECK_ARGUMENT_OPTIONS(VERBOSE, {});
            CHECK_ARGUMENT_OPTIONS(SILENT, {});
            CHECK_ARGUMENT_OPTIONS(COMPILE, {});
            CHECK_ARGUMENT_OPTIONS(MODULES, {});
            CHECK_ARGUMENT_OPTIONS(LIBS, {});
        }
    }
            
}