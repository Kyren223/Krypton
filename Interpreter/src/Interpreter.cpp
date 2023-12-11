// Copyright (c) 2023 Krypton. All rights reserved.

#include <lexer/Lexer.h>
#include "windows.h"

#ifndef NO_MAIN

int main(const int argc, const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    
    Lexer lexer("src/test.kr", R"('\176')");
    lexer.scanTokens();
    
    return 0;
}

#endif
