// Copyright (c) 2023 Krypton. All rights reserved.
#include <catch2/catch_test_macros.hpp>
#include <lexer/Lexer.h>
#include <lexer/Token.h>
#include <common/PrettyPrinter.h>

TEST_CASE("Lexer", "[lexer]")
{
    SECTION("Scan tokens")
    {
        Lexer lexer("src/test.kr", R"(true)");
        vector<Token> tokens = lexer.scanTokens();
        REQUIRE(tokens.size() == 2);
        REQUIRE(tokens[0].getType() == TokenType::TRUE);
        REQUIRE(tokens[1].getType() == TokenType::END);
    }
    
    SECTION("Scan tokens 2")
    {
        Lexer lexer("src/test.kr", R"(5.5 + "74" * 223 >= test true)");
        vector<Token> tokens = lexer.scanTokens();
        PrettyPrinter::print(tokens);
        REQUIRE(tokens.size() == 8 + 1); // +1 for END token
        REQUIRE(tokens[0].getType() == TokenType::DEC_LITERAL);
        REQUIRE(tokens[1].getType() == TokenType::PLUS);
        REQUIRE(tokens[2].getType() == TokenType::STRING_LITERAL);
        REQUIRE(tokens[3].getType() == TokenType::ASTERISK);
        REQUIRE(tokens[4].getType() == TokenType::INT_LITERAL);
        REQUIRE(tokens[5].getType() == TokenType::GREATER_EQUAL);
        REQUIRE(tokens[6].getType() == TokenType::IDENTIFIER);
        REQUIRE(tokens[7].getType() == TokenType::TRUE);
        REQUIRE(tokens[8].getType() == TokenType::END);
        
        REQUIRE((tokens[0].getLexeme().has_value() ? tokens[0].getLexeme().value() == "5.5" : false));
        REQUIRE((tokens[2].getLexeme().has_value() ? tokens[2].getLexeme().value() == "74" : false));
        REQUIRE((tokens[4].getLexeme().has_value() ? tokens[4].getLexeme().value() == "223" : false));
        REQUIRE((tokens[6].getLexeme().has_value() ? tokens[6].getLexeme().value() == "test" : false));
    }
}