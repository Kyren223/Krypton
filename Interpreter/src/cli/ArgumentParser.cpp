// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/ArgumentParser.h>

ArgumentParser::ArgumentParser(int argc, const char* argv[])
{
    // TODO: Implement parsing
}

optional<string> ArgumentParser::getPath() const
{
    return _path;
}

optional<variant<int, string>> ArgumentParser::getArgument(Argument type) const
{
    if (!_arguments.contains(type)) return {};
    return _arguments.at(type);
}
