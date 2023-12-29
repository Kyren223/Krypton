// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <types/Type.h>

using PrimitiveValue = variant<int, double, bool, unsigned char>;

struct Primitive
{
    static const Type BYTE;
    static const Type INT;
    static const Type DEC;
    static const Type BOOL;
    static const Type CHAR;
};
