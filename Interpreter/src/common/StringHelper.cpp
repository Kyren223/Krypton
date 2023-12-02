// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/StringHelper.h>

std::string StringHelper::toLower(const std::string& string)
{
    std::string result;
    for (char c : string)
    {
        if (c >= 'A' && c <= 'Z') result += std::to_string(c - ('A' - 'a'));
        else result += c;
    }
    return result;
}

std::string StringHelper::toUpper(const std::string& string)
{
    std::string result;
    for (char c : string)
    {
        if (c >= 'a' && c <= 'z') result += std::to_string(c + ('A' - 'a'));
        else result += c;
    }
    return result;
}
