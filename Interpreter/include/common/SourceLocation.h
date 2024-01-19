// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>

using std::string;

struct SourceLocation
{
    string filepath;
    int line;
    int column;
};