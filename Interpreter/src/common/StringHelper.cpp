// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/StringHelper.h>
#include <stdexcept>
#include <common/utf8.h>

string StringHelper::toLower(const string& str)
{
    string result;
    for (char c : str)
    {
        if (c >= 'A' && c <= 'Z') c -= ('A' - 'a');
        result += c;
    }
    return result;
}

string StringHelper::toUpper(const string& str)
{
    string result;
    for (char c : str)
    {
        if (c >= 'a' && c <= 'z') c += ('A' - 'a');
        result += c;
    }
    return result;
}

string StringHelper::trim(const string& str, char ch)
{
    string result;
    for (char c : str)
    {
        if (c != ch) result += c;
    }
    return result;
}

string StringHelper::replace(const string& str, const string& from, const string& to)
{
    throw std::runtime_error("Not implemented");
}

bool StringHelper::isUtf8(const string& str)
{
    return utf8::is_valid(str.begin(), str.end());
}

size_t StringHelper::getUtf8CharLength(const string& str)
{
    return utf8::unchecked::distance(str.begin(), str.end());
}

bool StringHelper::isAscii(const string& str)
{
    return getUtf8CharLength(str) == str.size();
}


