// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/CommandExecutor.h>
#include <common/Logger.h>
#include <common/Constants.h>

CommandExecutor::CommandExecutor(ArgumentParser& parser)
    : _parser(parser)
{
    // TODO Implement constructor
}

void CommandExecutor::execute()
{
    if (_parser.hasArgument(Argument::HELP))
    {
        executeHelp(_parser.getArgumentValue(Argument::HELP)));
    }
    else if (_parser.hasArgument(Argument::VERSION)) executeVersion();
    else if (_parser.getPath())
    {
        // TODO Implement build
    }
    else
    {
        Logger::error("No command specified!");
        Logger::log("Use \"krypton --help\" to see all commands");
    }
}

void CommandExecutor::executeHelp(optional<Argument> argument)
{
    string message;
    
    if (!argument)
    {
        message = "Usage: krypton <path> [arguments]\n"
                  "       krypton [arguments] \n"
                  "Path:\n"
                  "  Krypton File (.kr)\n"
                  "  Krypton AST (.kast)\n"
                  "  Directory (contains folders) \n\n"
                  "Arguments:\n"
                  "  -h, --help                Show help information\n"
                  "                            Add command name to show help for a specific command\n"
                  "  -v, --version             Show version information\n"
                  "  -b, --build               Build a Krypton File or Directory\n"
                  "                            Must add a build path if <path> is a directory\n"
                  "  -r, --run                 Run a <path> \n"
                  "  --include-subdirectories  Search for files inside subdirectories  \n"
                  "  --no-std                  Do not include the standard library\n"
                  "  --suppress-warnings       Do not show warnings\n"
                  "  --verbose                 Show verbose output\n"
                  "  --silent                  Do not show any output other than errors\n"
                  ;
    }
    
    switch (argument.value())
    {
        
        case Argument::HELP:
            message = "Help Usage:\n"
                      "  krypton --help\n"
                      "  krypton --help\"<argument>\"\n"
                      "Short: -h \n";
            break;
        case Argument::VERSION:
            message = "Version Usage:\n"
                      "  krypton --version\n"
                      "Short: -v \n";
            break;
        case Argument::BUILD:
            message = "Build Usage:\n"
                      "  krypton <Krypton File> --build\n"
                      "  krypton <Krypton File> --build\"<path>\"\n"
                      "  krypton <Directory> --build\"<path>\"\n"
                      "Short: -b \n";
            break;
        case Argument::RUN:break;
            message = "Run Usage:\n"
                      "  krypton <Krypton File> --run\n"
                      "  krypton <Krypton AST> --run\n"
                      "  krypton <Directory> --run\n"
                      "Short: -r \n";
        case Argument::INCLUDE_SUBDIRECTORIES:break;
            message = "Include Subdirectories Usage:\n"
                      "  krypton <Directory> --include-subdirectories\n"
                      "Short: None existent \n";
        case Argument::NO_STD:break;
            message = "No STD Usage:\n"
                      "  krypton <Directory> --no-std\n"
                      "Short: None existent \n";
        case Argument::SUPPRESS_WARNINGS:break;
            message = "Suppress Warnings Usage:\n"
                      "  krypton <path> --suppress-warnings\n"
                      "Short: None existent \n";
        case Argument::VERBOSE:break;
            message = "Verbose Usage:\n"
                      "  krypton <path> --verbose\n"
                      "Short: None existent \n";
        case Argument::SILENT:break;
            message = "Silent Usage:\n"
                      "  krypton <path> --silent\n"
                      "Short: None existent \n";
    }
    
    Logger::log(message);
}

void CommandExecutor::executeVersion()
{
    string interpreterString = Constants::APP_NAME;
    interpreterString += " v";
    interpreterString += Constants::VERSION;
    interpreterString += " (";
    interpreterString += Constants::STABLE ? "Stable" : "Unstable";
    interpreterString += " ";
    interpreterString += DEBUG ? "Debug" : "Release";
    interpreterString += " Build)";
    
    string languageString = Constants::LANGUAGE_NAME;
    languageString += " ";
    languageString += std::to_string(Constants::LANGUAGE_VERSION);
    
    Logger::log(interpreterString);
    Logger::log("Supports " + languageString);
}
