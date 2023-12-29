// Copyright (c) 2023 Krypton. All rights reserved.

#include <lexer/Lexer.h>
#include <parser/Parser.h>
#include <common/PrettyPrinter.h>
#include <common/Logger.h>
#include "windows.h"
#include <runtime/KryptonRuntime.h>

#include <utility>

#if DEBUG

// Override new and delete operators to track memory leaks

#define VERBOSE_TRACKING false
size_t allocated = 0;

void* operator new(size_t size)
{
    allocated += size;
    if (VERBOSE_TRACKING) printf("Allocated %zu bytes [%zu]\n", size, allocated);
    return malloc(size);
}

void operator delete(void* p, size_t size) noexcept
{
    allocated -= size;
    if (VERBOSE_TRACKING) printf("Deallocated %zu bytes [%zu]\n", size, allocated);
    free(p);
    if (allocated == 0) printf("\nFreed all memory\n");
}

#endif

#ifndef NO_MAIN

void execute(string source)
{
    Lexer lexer("src/test.kr", std::move(source));
    vector<Token> tokens = lexer.scanTokens();
    PrettyPrinter::print(tokens);
    Parser parser(tokens);
    unique_ptr<ASTNode> ast = parser.parse();
    PrettyPrinter::print(*ast);
    KryptonRuntime runtime(std::move(ast));
    runtime.run();
}

void loop()
{
    while (true)
    {
        Logger::print(LogMode::NONE, ">>> ", Color::WHITE);
        char input[256];
        scanf("%[^\n]%*c", input);
        if (strcmp(input, "exit") == 0) exit(0);
        execute(input);
    }
}

int main(const int argc, const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    
    loop();
//    execute(R"(5 + 7 * 30 / 10 + (65 + 5) * 50)");
//    printf("Result: %d\n", 5 + 7 * 30 / 10 + (65 + 5) * 50);

    return 0;
}

#endif
