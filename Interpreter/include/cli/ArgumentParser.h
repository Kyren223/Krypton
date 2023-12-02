// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <optional>
#include <unordered_map>
#include <variant>
#include <cli/Argument.h>

using std::optional, std::string, std::unordered_map, std::variant, std::pair;

class ArgumentParser
{
    optional<string> _path;
    unordered_map<Argument, optional<string>> _arguments;

public:
    ArgumentParser(int argc, const char* argv[]);

    optional<string> getPath() const;
    bool hasArgument(Argument type) const;
    optional<string> getArgumentValue(Argument type) const;

    static string argumentToString(Argument argument);
    static optional<Argument> argumentFromString(const string& argument);

private:
    pair<Argument, optional<string>> parseArgument(string argument) const;
    static int getDashCount(string argument);
};
