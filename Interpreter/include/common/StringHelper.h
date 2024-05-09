// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once
#include <string>

using std::string;

class StringHelper
{
public:
    static string toLower(const string& str);
    static string toUpper(const string& str);
    static string trim(const string& str, char ch);
    static string replace(const string& str, const string& from, const string& to);
    
    // UTF-8
    static size_t getUtf8CharLength(const string& str);
    static bool isUtf8(const string& str);
    static bool isAscii(const string& str);
};

