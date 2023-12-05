// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/ArgumentParser.h>
#include <common/Logger.h>
#include <common/FileHelper.h>
#include <common/StringHelper.h>

ArgumentParser::ArgumentParser(int argc, const char* argv[])
{
    #if DEBUG
        Logger::debug("ArgumentParser - List of arguments:");
        for (int i = 0; i < argc; i++) Logger::debug(argv[i]);
    #endif
    
    _terminate = false;
    _index = 0;
    _input = vector<string>(argv + 1, argv + argc);
    
    while (_index < _input.size()) parseNextArgument();
    
    if (_terminate)
    {
        Logger::log("Use \"krypton --help\" to see all arguments");
        exit(1);
    }
}

bool ArgumentParser::hasArgument(Argument type) const
{
    return _arguments.contains(type);
}

int ArgumentParser::getDashCount(string argument)
{
    int count = 0;
    if (argument[0] == '-') count++;
    if (argument[1] == '-') count++;
    return count;
}

optional<string> ArgumentParser::argumentToString(const Argument argument)
{
    switch (argument)
    {
        case Argument::PATH: return "PATH";
        case Argument::HELP: return "HELP";
        case Argument::VERSION: return "VERSION";
        case Argument::BUILD: return "BUILD";
        case Argument::RUN: return "RUN";
        case Argument::INCLUDE_SUBDIRECTORIES: return "INCLUDE_SUBDIRECTORIES";
        case Argument::NO_STD: return "NO_STD";
        case Argument::SUPPRESS_WARNINGS: return "SUPPRESS_WARNINGS";
        case Argument::VERBOSE: return "VERBOSE";
        case Argument::SILENT: return "SILENT";
        case Argument::COMPILE: return "COMPILE";
        case Argument::MODULES: return "MODULES";
        case Argument::LIBS: return "LIBS";
    }
    return {};
}

optional<Argument> ArgumentParser::argumentFromString(const string& argument)
{
    string upperArgument = StringHelper::toUpper(argument);
    if (upperArgument == "PATH") return Argument::PATH;
    if (upperArgument == "HELP") return Argument::HELP;
    if (upperArgument == "VERSION") return Argument::VERSION;
    if (upperArgument == "BUILD") return Argument::BUILD;
    if (upperArgument == "RUN") return Argument::RUN;
    if (upperArgument == "INCLUDE_SUBDIRECTORIES") return Argument::INCLUDE_SUBDIRECTORIES;
    if (upperArgument == "NO_STD") return Argument::NO_STD;
    if (upperArgument == "SUPPRESS_WARNINGS") return Argument::SUPPRESS_WARNINGS;
    if (upperArgument == "VERBOSE") return Argument::VERBOSE;
    if (upperArgument == "SILENT") return Argument::SILENT;
    if (upperArgument == "COMPILE") return Argument::COMPILE;
    if (upperArgument == "MODULES") return Argument::MODULES;
    if (upperArgument == "LIBS") return Argument::LIBS;
    return {};
}

vector<string> ArgumentParser::getArgumentOptions(Argument type) const
{
    if (!_arguments.contains(type)) return {};
    return _arguments.at(type);
}

void ArgumentParser::parseNextArgument()
{
    Logger::debug("ArgumentParser - Parsing argument: " + _input[_index]);
    
    optional<Argument> type;
    string argument = _input[_index];
    int dashCount = getDashCount(argument);
    
    if (dashCount == 0)
    {
        /*
         * Note: the only case where dashCount is 0 is at the start
         * Because if it's not at the start, it will get parsed as an option
         * Options only terminate for the current argument if it encounters:
         * 1. A dash (new argument)
         * 2. The end of the input
         * So we can assume this is the first argument which we interpret as the path
         */
        type = Argument::PATH;
    }
    else
    {
        type = getArgumentType(argument, dashCount);
        _index++;
    }
    
    vector<string> options;
    while (true)
    {
        if (_index >= _input.size()) break;
        string option = _input.at(_index);
        if (getDashCount(option) != 0) break;
        
        options.push_back(option);
        _index++;
        
        Logger::debug("ArgumentParser - Parsing option: " + option);
    }
    
    if (type) _arguments[type.value()] = options;
    else
    {
        Logger::error("Invalid argument: " + argument);
        _terminate = true;
    }
}

optional<Argument> ArgumentParser::getArgumentType(const string& argument, int dashCount)
{
    if (dashCount == 2)
    {
        string arg = StringHelper::toUpper(argument).substr(2);
        return argumentFromString(arg);
    }
    
    string arg = StringHelper::toLower(argument.substr(1));
    if (arg.size() != 1) return {};
    char ch = arg[0];
    switch (ch)
    {
        case 'p': return Argument::PATH;
        case 'h': return Argument::HELP;
        case 'v': return Argument::VERSION;
        case 'b': return Argument::BUILD;
        case 'r': return Argument::RUN;
        case 'i': return Argument::INCLUDE_SUBDIRECTORIES;
        case 'n': return Argument::NO_STD;
        case 'w': return Argument::SUPPRESS_WARNINGS;
        case 'c': return Argument::COMPILE;
        case 'm': return Argument::MODULES;
        case 'l': return Argument::LIBS;
        case 's': return Argument::SILENT;
        case 'o': return Argument::VERBOSE;
        default: return {};
    }
}
