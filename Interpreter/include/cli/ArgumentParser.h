// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <cli/Argument.h>

using std::optional, std::string, std::unordered_map, std::vector;

class ArgumentParser
{
    unordered_map<Argument, vector<string>> _arguments;
    vector<string> _input;
    int _index;
    bool _terminate;

public:
    ArgumentParser(int argc, const char* argv[]);

    bool hasArgument(Argument type) const;
    vector<string> getArgumentOptions(Argument type) const;

    static optional<string> argumentToString(Argument argument);
    static optional<Argument> argumentFromString(const string& argument);

private:
    void parseNextArgument();
    static int getDashCount(string argument);
    static optional<Argument> getArgumentType(const string& argument, int dashCount);
};
