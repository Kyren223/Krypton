// Copyright (c) 2023 Krypton. All rights reserved.
#include <catch2/catch_test_macros.hpp>
#include <common/PrettyPrinter.h>
#include <parser/Parser.h>
#include <lexer/Lexer.h>

TEST_CASE("Parser", "[parser]")
{
    SECTION("Parse expressions")
    {
        Lexer lexer("src/test.kr", R"(5.5 + "74" * 223 >= test true)");
        vector<Token> tokens = lexer.scanTokens();
        Parser parser(tokens);
        unique_ptr<ASTNode> node = parser.parse();
        PrettyPrinter::print(*node);
        
        
    }
}