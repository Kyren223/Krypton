// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <optional>
#include <unordered_map>
#include <variant>
#include <cli/Argument.h>

using std::optional, std::string, std::unordered_map, std::variant;

class ArgumentParser
{
    optional<string> _path;
    unordered_map<Argument, variant<int, string>> _arguments;

public:
    ArgumentParser(int argc, const char* argv[]);
    
    optional<string> getPath() const;
    optional<variant<int, string>> getArgument(Argument type) const;
};
