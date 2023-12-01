// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/ArgumentParser.h>
#include <cli/CommandExecutor.h>
#include <common/Logger.h>
#include <common/Constants.h>

#ifndef NO_MAIN

int main(const int argc, const char* argv[])
{
    std::string build = Constants::NAME;
    build += " v";
    build += Constants::VERSION;
    build += " (";
    build += Constants::STABLE ? "Stable" : "Unstable";
    build += " ";
    build += DEBUG ? "Debug" : "Release";
    build += " Build)";
    
    Logger::log(build);
    
    ArgumentParser parser(argc, argv);
    CommandExecutor executor(parser);
    executor.execute();
    
    return 0;
}

#endif
