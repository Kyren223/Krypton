// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <optional>

using std::string, std::optional;

struct SourceLocation
{
    string filepath;
    int line;
    int column;
};

struct SyntaxError
{
    SourceLocation location;
    string line;
    optional<string> length;
    string message;
};





