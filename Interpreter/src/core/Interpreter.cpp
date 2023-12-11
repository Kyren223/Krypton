// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/ArgumentParser.h>
#include <cli/CommandExecutor.h>
#include <lexer/Lexer.h>

#ifndef NO_MAIN

int main(const int argc, const char* argv[])
{
//    ArgumentParser parser(argc, argv);
//    CommandExecutor executor(parser);
//    executor.execute();
    Lexer lexer("src/test.kr", "var a = 10;");
    lexer.scanTokens();
    
    Lexer lexer2("src/test.kr", "var a = ~10;");
    lexer2.scanTokens();
    
    
    
    return 0;
}

#endif
