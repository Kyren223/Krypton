// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/StringHelper.h>

string StringHelper::toLower(const string& s)
{
    string result;
    for (char c : s)
    {
        if (c >= 'A' && c <= 'Z') result += std::to_string(c - ('A' - 'a'));
        else result += c;
    }
    return result;
}

string StringHelper::toUpper(const string& s)
{
    string result;
    for (char c : s)
    {
        if (c >= 'a' && c <= 'z') result += std::to_string(c + ('A' - 'a'));
        else result += c;
    }
    return result;
}
