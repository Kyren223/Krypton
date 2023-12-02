// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include "ArgumentParser.h"

class CommandExecutor
{
    ArgumentParser& _parser;
    
public:
    explicit CommandExecutor(ArgumentParser& parser);
    void execute();
    
private:
    void executeHelp(optional<Argument> argument);
    void executeVersion();
};
