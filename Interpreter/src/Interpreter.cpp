// Copyright (c) 2023 Krypton. All rights reserved.

#include <lexer/Lexer.h>
#include <parser/Parser.h>
#include <common/PrettyPrinter.h>
#include <common/Logger.h>
#include "windows.h"
#include <runtime/KryptonRuntime.h>

#include <utility>
#include <common/FileHelper.h>
#include <runtime/KryptonSTD.h>

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

void execute(string file, string source, Environment& env)
{
    Lexer lexer(file, std::move(source));
    vector<Token> tokens = lexer.scanTokens();
//    if (DEBUG == true) PrettyPrinter::print(tokens);
    Parser parser(tokens);
    unique_ptr<ASTNode> ast = parser.parse();
//    PrettyPrinter::print(*ast);
    KryptonRuntime runtime(std::move(ast), env);
    runtime.run();
}

void repl()
{
    ErrorHandler::getInstance().setReplMode(true);
    Environment env;
    KryptonSTD::load(env);
    Logger::print(LogMode::NONE, "==== Krypton REPL ====", Color::BLUE);
    while (true)
    {
        ErrorHandler::getInstance().reset();
        Logger::print(LogMode::NONE, "\n>>> ", Color::WHITE);
        char input[1024];
        scanf("%[^\n]%*c", input);
        if (strcmp(input, "exit") == 0) exit(0);
        
        try { execute("Terminal - repl", input, env); }
        catch (const std::exception& e) {}
    }
}

void runFile(const string& filepath)
{
    ErrorHandler::getInstance().setReplMode(false);
    Environment env;
    KryptonSTD::load(env);
    optional<string> source = FileHelper::readFile(filepath);
    if (!source.has_value())
    {
        Logger::error("Failed to read file - " + filepath);
        exit(1);
    }
    execute(filepath, source.value(), env);
}

int main(const int argc, const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    if (argc == 1) repl();
    if (argc == 2) runFile(argv[1]);
    else
    {
        Logger::error("Invalid arguments");
        Logger::print(LogMode::NONE, "Usage: \n"
                                     "\tkrypton [path] - Execute file\n"
                                     "\tkrypton - Go into REPL mode\n", Color::BLUE);
        exit(1);
    }
    
    return 0;
}

#endif
