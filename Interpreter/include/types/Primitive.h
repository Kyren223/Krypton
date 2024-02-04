// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <types/Type.h>
#include <nodes/FunctionNodes.h>

using PrimitiveValue = variant<int, double, bool, unsigned char, string, const LambdaExpression*>;

struct Primitive
{
    static const Type INT;
    static const Type DEC;
    static const Type BOOL;
    static const Type CHAR;
    static const Type STR;
    static const Type FUNC;
};
