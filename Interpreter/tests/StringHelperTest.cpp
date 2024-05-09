// Copyright (c) 2023 Krypton. All rights reserved.
#include <catch2/catch_test_macros.hpp>
#include <common/StringHelper.h>

TEST_CASE("StringHelper")
{
    SECTION("toUpper")
    {
        REQUIRE(StringHelper::toUpper("Hello World!") == "HELLO WORLD!");
    }
    
    SECTION("toLower")
    {
        REQUIRE(StringHelper::toLower("Hello World!") == "hello world!");
    }
    
    SECTION("trim")
    {
        REQUIRE(StringHelper::trim("Hello World!", 'l') == "Heo Word!");
    }
}

