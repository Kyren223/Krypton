// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <cstdint>

using std::uint8_t;

enum class BinaryOperation : uint8_t
{
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    PERCENT,
    CARET,
};

enum class UnaryOperation : uint8_t
{
    PLUS_PLUS,
    MINUS_MINUS,
};
