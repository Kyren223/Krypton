// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/ArgumentParser.h>
#include <cli/CommandExecutor.h>
#include <lexer/Lexer.h>
#include "windows.h"

#ifndef NO_MAIN

int main(const int argc, const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
//    ArgumentParser parser(argc, argv);
//    CommandExecutor executor(parser);
//    executor.execute();

    Lexer lexer("src/test.kr", "'あ'あ");
    lexer.scanTokens();
    
    
    
    
    return 0;
}

#endif
