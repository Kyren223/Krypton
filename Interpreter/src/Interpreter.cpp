// Copyright (c) 2023 Krypton. All rights reserved.

#include <lexer/Lexer.h>
#include "windows.h"

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
    if (allocated == 0) printf("Freed all memory\n");
}

#endif

#ifndef NO_MAIN

int main(const int argc, const char* argv[])
{
    {
        SetConsoleOutputCP(CP_UTF8);
        
        Lexer lexer("src/test.kr", R"('\176')");
        lexer.scanTokens();
    }
    return 0;
}

#endif
