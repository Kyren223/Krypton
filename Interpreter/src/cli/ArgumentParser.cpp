// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/ArgumentParser.h>
#include <common/Logger.h>
#include <stdexcept>

ArgumentParser::ArgumentParser(int argc, const char* argv[])
{
#if DEBUG
    Logger::debug("ArgumentParser - List of arguments:");
    for (int i = 0; i < argc; i++)
    {
        Logger::debug(argv[i]);
    }
#endif

    try
    {
        _path = argv[1][0] != '-' ? argv[1] : optional<string>();
        Logger::debug("ArgumentParser - Path: " + (_path ? _path.value() : "None"));
        for (int i = 2; i < argc; i++)
        {
            auto argument = parseArgument(argv[i]);
            _arguments.insert(argument);
        }
    }
    catch (std::invalid_argument& e) { Logger::error(e.what()); }

}

optional<string> ArgumentParser::getPath() const
{
    return _path;
}

bool ArgumentParser::hasArgument(Argument type) const
{
    return _arguments.contains(type);
}

optional<string> ArgumentParser::getArgumentValue(Argument type) const
{
    if (!_arguments.contains(type)) return {};
    return _arguments.at(type);
}

pair<Argument, optional<string>> ArgumentParser::parseArgument(string argument) const
{
    int dashes = getDashCount(argument);
    if (dashes == 0) throw std::invalid_argument("Argument " + argument + " must start with a dash");
    
    
    Argument argumentType;
    optional<string> argumentValue;
    if (dashes == 1)
    {
        switch (argument[1])
        {
            case 'h':
                argumentType = Argument::HELP;
                argumentValue = argument.substr(2);
                break;
            case 'v':
                argumentType = Argument::VERSION;
                break;
            case 'b':
                argumentType = Argument::BUILD;
                argumentValue = argument.substr(2);
                break;
            case 'r':
                argumentType = Argument::RUN;
                break;
            default:
                throw std::invalid_argument("Invalid argument");
        }
    }
    if (dashes == 2)
    {
        if (argument.starts_with("--help"))
        {
            argumentType = Argument::HELP;
            argumentValue = argument.substr(7);
        }
        else if (argument.starts_with("--version"))
        {
            argumentType = Argument::VERSION;
        }
        else if (argument.starts_with("--build"))
        {
            argumentType = Argument::BUILD;
            argumentValue = argument.substr(8);
        }
        else if (argument.starts_with("--run"))
        {
            argumentType = Argument::RUN;
        }
        else if (argument.starts_with("--include-subdirectories"))
        {
            argumentType = Argument::INCLUDE_SUBDIRECTORIES;
        }
        else if (argument.starts_with("--no-std"))
        {
            argumentType = Argument::NO_STD;
        }
        else if (argument.starts_with("--suppress-warnings"))
        {
            argumentType = Argument::SUPPRESS_WARNINGS;
        }
        else if (argument.starts_with("--verbose"))
        {
            argumentType = Argument::VERBOSE;
        }
        else if (argument.starts_with("--silent"))
        {
            argumentType = Argument::SILENT;
        }
        else
        {
            throw std::invalid_argument("Invalid argument");
        }
    }

#if DEBUG
    Logger::debug("ArgumentParser - Argument type: " + argumentToString(argumentType));
    Logger::debug("ArgumentParser - Argument value: " + (argumentValue ? argumentValue.value() : "None"));
#endif
    
    return {argumentType, argumentValue};
}

int ArgumentParser::getDashCount(string argument)
{
    int count = 0;
    if (argument[0] == '-') count++;
    if (argument[1] == '-') count++;
    return count;
}

string ArgumentParser::argumentToString(const Argument argument)
{
    switch (argument)
    {
        case Argument::HELP: return "HELP";
        case Argument::VERSION: return "VERSION";
        case Argument::BUILD: return "BUILD";
        case Argument::RUN: return "RUN";
        case Argument::INCLUDE_SUBDIRECTORIES: return "INCLUDE_SUBDIRECTORIES";
        case Argument::NO_STD: return "NO_STD";
        case Argument::SUPPRESS_WARNINGS: return "SUPPRESS_WARNINGS";
        case Argument::VERBOSE: return "VERBOSE";
        case Argument::SILENT: return "SILENT";
    }
    return "None";
}

optional<Argument> ArgumentParser::argumentFromString(string argument)
{
    if (argument == "HELP") return Argument::HELP;
    if (argument == "VERSION") return Argument::VERSION;
    if (argument == "BUILD") return Argument::BUILD;
    if (argument == "RUN") return Argument::RUN;
    if (argument == "INCLUDE_SUBDIRECTORIES") return Argument::INCLUDE_SUBDIRECTORIES;
    if (argument == "NO_STD") return Argument::NO_STD;
    if (argument == "SUPPRESS_WARNINGS") return Argument::SUPPRESS_WARNINGS;
    if (argument == "VERBOSE") return Argument::VERBOSE;
    if (argument == "SILENT") return Argument::SILENT;
    return {};
}
