// Copyright (c) 2023 Krypton. All rights reserved.
#include <cli/ArgumentParser.h>
#include <cli/CommandExecutor.h>

#ifndef NO_MAIN

int main(const int argc, const char* argv[])
{
    ArgumentParser parser(argc, argv);
    CommandExecutor executor(parser);
    executor.execute();
    
    return 0;
}

#endif
