// Copyright (c) 2023 Krypton. All rights reserved.
#include <catch2/catch_test_macros.hpp>
#include <common/Logger.h>

TEST_CASE("Logger")
{
    
    Logger::info("This is an info!");
    Logger::warn("This is a warning!");
    Logger::error("This is an error!");
    Logger::debug("This is a debug!");
}